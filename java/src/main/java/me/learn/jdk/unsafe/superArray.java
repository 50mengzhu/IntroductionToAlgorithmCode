package me.learn.jdk.unsafe;

import java.lang.reflect.Field;

import sun.misc.Unsafe;


/**
 * 通过  {@link Unsafe#allocateMemory(long)}进行堆外内存的分配
 * 就可以突破java中对于最长数组的限制，在java中数组最长为{@link Integer#MAX_VALUE}
 * 我们进行堆外内存分配就可以超过这个限制；但是由于是堆外分配的内存不受java虚拟机的管理
 * 因此需要注意小心使用.
 */
public class superArray {

    private static Unsafe unsafe;

    static {
        try {
            Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
            theUnsafe.setAccessible(true);
            unsafe = (Unsafe) theUnsafe.get(null);
        } catch (NoSuchFieldException | IllegalAccessException e) {
            e.printStackTrace();
        }
    }

    private static final int BYTE = 1;

    private long size;

    private long address;

    public superArray(long size) {
        this.size = size;
        address = unsafe.allocateMemory(size * BYTE);
        unsafe.setMemory(address, size, (byte) 0);
    }

    public void set(long i, byte value) {
        unsafe.putByte(address, i, value);
    }

    public byte get(long i) {
        return unsafe.getByte(address + i * BYTE);
    }

    public long size() {
        return size;
    }

    public static void main(String[] args) {
        long SUPER_LENGTH = (long) Integer.MAX_VALUE + 2;
        superArray array = new superArray(SUPER_LENGTH);
        System.out.println(array.size());
        int sum = 0;
        for (int i = 0; i < 2; ++ i) {
            array.set((long) Integer.MAX_VALUE + i, (byte) 1);
            sum += array.get((long) Integer.MAX_VALUE + i);
        }
        System.out.println(sum);
    }
}
