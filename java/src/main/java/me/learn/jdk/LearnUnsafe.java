package me.learn.jdk;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.HashSet;
import java.util.Set;

import org.openjdk.jol.info.ClassLayout;
import sun.misc.Unsafe;

public class LearnUnsafe {

    private static Unsafe getUnsafe() throws Exception {
        Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
        theUnsafe.setAccessible(true);
        Unsafe unsafe = (Unsafe) theUnsafe.get(null);
        return unsafe;
    }


    public static long sizeOf(Object o) throws Exception {
        Unsafe unsafe = getUnsafe();
        Set<Field> fields = new HashSet<>();
        Class clazz = o.getClass();
        while (clazz != Object.class) {
            for (Field f : o.getClass().getDeclaredFields()) {
                if ((f.getModifiers() & Modifier.STATIC) == 0) {
                    fields.add(f);
                }
            }
            clazz = clazz.getSuperclass();
        }

        long maxSize = 0;
        for (Field f : fields) {
            long offset = unsafe.objectFieldOffset(f);
            if (offset > maxSize) {
                offset = maxSize;
            }
        }

        return ((maxSize / 8) + 1) * 8;

    }


    public static void main(String[] args) throws Exception {
        Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
        theUnsafe.setAccessible(true);
        Unsafe unsafe = (Unsafe) theUnsafe.get(null);

        Guard guard = new Guard();
        System.out.println(ClassLayout.parseInstance(guard).toPrintable());
        System.out.println(guard.giveAccess());
//        Field field = guard.getClass().getDeclaredField("ACCESS_ALLOWED_2");
//        unsafe.putInt(guard, unsafe.objectFieldOffset(field), 42);
        System.out.println(guard.giveAccess());

        System.out.println(sizeOf(Guard.class));


        Field string = Guard.class.getDeclaredField("string");
        Field aDouble = Guard.class.getDeclaredField("aDouble");
        Field bDouble = Guard.class.getDeclaredField("bDouble");
        System.out.println(unsafe.objectFieldOffset(string));
        System.out.println(unsafe.objectFieldOffset(aDouble));
        System.out.println(unsafe.objectFieldOffset(bDouble));
//        System.out.println(unsafe.objectFieldOffset(field));


        System.out.println(ClassLayout.parseInstance(guard).toPrintable());
    }


}
