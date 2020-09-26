package me.learn.jdk;

import java.lang.reflect.Field;

import sun.misc.Unsafe;

public class TestUnsafe {

    private Guard guard;


    private Unsafe getUnsafe() {
        Unsafe unsafe = null;
        try {
            Field theUnsafe = Unsafe.class.getDeclaredField("theUnsafe");
            theUnsafe.setAccessible(true);
            unsafe = (Unsafe) theUnsafe.get(null);
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
            return null;
        } catch (IllegalAccessException e) {
            e.printStackTrace();
            return null;
        }
        return unsafe;
    }

    private void alloc() {
        Unsafe unsafe = getUnsafe();
        long base = unsafe.allocateMemory(40L);
        unsafe.setMemory(guard, 12, 1, (byte) 0);
    }
}
