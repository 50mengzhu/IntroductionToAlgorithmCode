package me.learn.jdk.unsafe;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.concurrent.TimeUnit;

import sun.misc.Unsafe;

/**
 * 以下介绍了关于 {@link Unsafe}类的相关的一些使用方法
 * 可以参考在 jdk中使用到这个方法的一些操作
 * https://zhuanlan.zhihu.com/p/56772793
 * 这个类提供的方法实际上像为 java语言开了一扇后门
 * 用于直接和内存进行交互，实现了和 c语言一样的那种
 * molloc/memset/free等方法。以及操作系统级别的一些操作
 *
 * @author mica
 */
public class LearnUnsafe {

    /**
     * 第一步：获取到 unsafe类进行操作，获取 unsafge对象的实例可以通过
     * {@link Unsafe#getUnsafe()}静态方法直接获取，但是由于 Unsafe类
     * 中对加载类有比较严格的限制，因此还可以通过万能的 java反射直接获取到
     * unsafe实例对象
     *
     * @return unsafe实例对象
     */
    private Unsafe getUnsafe() {
        try {
            Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
            theUnsafe.setAccessible(true);
            Unsafe unsafe = (Unsafe) theUnsafe.get(null);
            return unsafe;
        } catch (NoSuchFieldException | IllegalAccessException e) {
            e.printStackTrace();
            return null;
        }
    }

    /**
     * 通过 unsafe类操作数组，可以通过 {@link Unsafe#arrayBaseOffset(Class)}
     * 获取对应数组类中的通用起始地址偏移量；通过{@link Unsafe#arrayIndexScale(Class)}
     * 获取对于数组类中的通用元素大小。
     * 然后可以通过以下的方式直接定位到数组的地址 ——
     * <code>
     *     address: base + scale * i
     *     content: array[i]
     * </code>
     *
     * 然后可以通过{@link Unsafe#getObject(Object, long)}可以直接获取指定数组在偏移量为i
     * 处地址中的内容；同时也可以通过{@link Unsafe#putObject(Object, long, Object)}对
     * 指定的数组中的偏移量为 i地址中的内容进行直接写。
     */
    public void operateArray() {
        String[] strs = new String[] {"1", "2", "3"};
        Unsafe unsafe = getUnsafe();
        int i = unsafe.arrayBaseOffset(String[].class);
        System.out.println("base offset is " + i);

        int i1 = unsafe.arrayIndexScale(String[].class);
        System.out.println("scale is " + i1);

        System.out.println("first string of str is " + unsafe.getObject(strs, i));
        try {
            unsafe.putObject(strs, i + i1 * 0, "dx");
            System.out.println("first string of str" + unsafe.getObject(strs, i + i1 * 0));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    /**
     * 操作对象
     *
     * <ul>
     *     <li>
     *          跳过构造方法，对对象进行实例化操作，然后可以直接对{@link Unsafe#allocateInstance(Class)}
     *          获取到的对象进行复制，传递参数
     *     </li>
     *     <li>
     *         可以通过{@link Unsafe#allocateInstance(Class)}创建对象，然后根据对象实例中的属性名称获取
     *         对应的偏移量，然后内存级修改对象的值
     *     </li>
     *     <li>
     *         对象的反序列化
     *         当使用框架反序列化或者构建对象时，会假设从已存在的对象中重建，你期望使用反射来调用类的设置函数，
     *         或者更准确一点是能直接设置内部字段甚至是final字段的函数。问题是你想创建一个对象的实例，
     *         但你实际上又不需要构造函数，因为它可能会使问题更加困难而且会有副作用。
     *     </li>
     * </ul>
     *
     */
    private void operationObject() {
        Unsafe unsafe = getUnsafe();

        // 跳过构造方法，实例化对象
        try {
            // 通过 unsafe能够跳过构造函数，但还是会将整个类加载进来
            Data data = (Data) unsafe.allocateInstance(Data.class);
            data.setId(1);
            data.setName("hello");
            System.out.println(data);

            // 内存级别修改对象的属性
            Field name = Data.class.getDeclaredField("name");
            long offset = unsafe.objectFieldOffset(name);
            unsafe.putObject(data, offset, "world!");
            System.out.println(data);

        } catch (InstantiationException | NoSuchFieldException e) {
            e.printStackTrace();
        }

        // 这种用法目前看不太懂，
        // 我们可以在运行时创建一个类，比如从已编译的.class文件中。将类内容读取为字节数组，
        // 并正确地传递给defineClass方法；当你必须动态创建类，而现有代码中有一些代理， 这是很有用的
        try {
            File file = new File("F:\\work\\codeOJ\\IntroductionToAlgorithmCode\\java\\build\\classes\\java\\main\\me\\learn\\jdk\\unsafe\\Data.class");
            FileInputStream inputStream = new FileInputStream(file);
            byte[] content = new byte[(int) file.length()];
            inputStream.read(content);
            Class<?> aClass = unsafe.defineClass(null, content, 0, content.length, null, null);
            aClass.getMethod("getId").invoke(aClass.newInstance(), null);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        }

        // 操作内存
        long addr = unsafe.allocateMemory(8L);
        // setMemory是对内存地址进行初始化的一个方法
        // 和 c语言中的 memset比较类似
        unsafe.setMemory(addr, 8L, (byte) 1);
        System.out.println("get addr : " + unsafe.getInt(addr));

        //设置0-3 4个byte为0x7fffffff
        unsafe.putInt(addr, 0x7fffffff);
        //设置4-7 4个byte为0x80000000
        unsafe.putInt(addr + 4, 0x80000000);
        System.out.println("low memory: " + unsafe.getInt(addr));
        System.out.println("low memory: " + unsafe.getInt(addr + 4));
        unsafe.freeMemory(addr);
        System.out.println("low memory: " + unsafe.getInt(addr));
    }

    /**
     * cas操作，在 java的乐观锁就是采用的这样的一种方式进行的操作的
     * cas实际上对应的是一个这样的cpu指令 cmpxchg实现的原子性操作
     * 在操作系统层面上保证原子性，这样的操作是一种无锁的操作
     *
     *
     * TODO 待解决的问题
     * 不过这里仍然存在一个问题，这里 {@link Data}的结构如下的时候
     * <code>
     *      private Integer id
     * </code>
     * 我们在下面的代码中调用以下的方式是无法进行原子操作的。执行下面的代码运行结果为
     * <code>
     *     hello
     *     1 :null
     *     offset is 12
     *     false
     *     1 :null
     * </code>
     * 是以上的结果，但是当{@link Data}中的属性修改为如下的时候
     * <code>
     *     private int id
     * </code>
     * 下面的代码却能够正常进行 CAS操作
     * <code>
     *  hello
     *  1 :null
     *  offset is 12
     *  true
     *  2 :null
     * </code>
     *
     */
    public void casOpera() {
        Unsafe unsafe = getUnsafe();
        Data data = new Data();
        data.setId(1);
        System.out.println(data);
        try {
            Field id = Data.class.getDeclaredField("id");
            long objectFieldOffset = unsafe.objectFieldOffset(id);
            System.out.println("offset is " + objectFieldOffset);
            id.setAccessible(true);
            boolean b = unsafe.compareAndSwapInt(data, objectFieldOffset, 1, 2);
            System.out.println(b);
            System.out.println(data);
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
    }

    /**
     * 职业那个可以打印出操作系统的一些相关信息。
     */
    public void osInfo() {
        Unsafe unsafe = getUnsafe();
        System.out.println(unsafe.addressSize());
        System.out.println(unsafe.pageSize());
        System.out.println(Unsafe.ARRAY_INT_BASE_OFFSET);
    }

    /**
     * 使用 unsafe对线程进行同步，主要的用法就是当调用
     * {@link Unsafe#park(boolean, long)}就会将当前线程挂起
     * 除非挂起的线程处于 {@link Thread#interrupt()}或者等待时间已经到了。
     * 上述方法中的第一个参数如果设置为 <code>true</code>，那么第二个参数将会
     * 启动绝对计时，单位为微秒；如果第一个参数设置为<code>false</code>，
     * 那么第二个参数将会启动相对计时，时间也更加精准，单位为纳秒。
     *
     * 对于处于{@link Unsafe#park(boolean, long)}之后的线程可以通过调用
     * {@link Unsafe#unpark(Object)}来进行唤醒
     */
    public void operaThread() {
        Unsafe unsafe = getUnsafe();
        Thread packThread = new Thread(() -> {
            long startTime = System.currentTimeMillis();
            // ps。。我这里写的好像是 毫秒
            unsafe.park(false, 500000000000L);
            System.out.println("main thread end,cost :"+(System.currentTimeMillis()-startTime)+"ms");
        });
        packThread.start();
        try {
            TimeUnit.SECONDS.sleep(1);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        unsafe.unpark(packThread);
    }


    public static void main(String[] args) {
        new LearnUnsafe().operaThread();
    }
}
