package me.learn.datastruct.seqlist;

import static org.testng.Assert.*;

import org.testng.annotations.Test;

public class ManacherAlgoTest {


    @Test
    public void testMannacher() {
        ManacherAlgo algo = new ManacherAlgo();
        String str1 = "12212";
        algo.manacher(str1);
    }

}