package me.learn.datastruct.seqlist;

import org.testng.Assert;
import org.testng.annotations.BeforeTest;
import org.testng.annotations.Test;

public class PalindromeProblemTest {

    private PalindromeProblem palindromeProblem;

    @BeforeTest
    public void before() {
        palindromeProblem = new PalindromeProblem();
    }


    @Test
    public void testWay1String() {
        boolean notTrue = palindromeProblem.way1String("abbc");
        Assert.assertFalse(notTrue);
        boolean maybeTrue = palindromeProblem.way1String("aaaaa");
        Assert.assertTrue(maybeTrue);
        boolean mustTrue = palindromeProblem.way1String("abcdeedcba");
        Assert.assertTrue(mustTrue);
        boolean test1 = palindromeProblem.way1String("ahhhhha");
        Assert.assertTrue(test1);
    }

    @Test
    public void testWay2String() {
        boolean notTrue = palindromeProblem.way2String("abbc");
        Assert.assertFalse(notTrue);
        boolean maybeTrue = palindromeProblem.way2String("aaaaa");
        Assert.assertTrue(maybeTrue);
        boolean mustTrue = palindromeProblem.way2String("abcdeedcba");
        Assert.assertTrue(mustTrue);
        boolean test1 = palindromeProblem.way2String("ahhhhha");
        Assert.assertTrue(test1);
        boolean test2 = palindromeProblem.way2String("amanaplanacanalpanama");
        Assert.assertTrue(test2);
    }


    @Test
    @SuppressWarnings("unchecked")
    public void testWay1LinkList() throws CloneNotSupportedException {
        PalindromeProblem.LinkList<Integer> list = new PalindromeProblem.LinkList();
        list.addAll(new Integer[]{1, 2, 2, 3});
        boolean notTrue = palindromeProblem.way1LinkList(list);
        Assert.assertFalse(notTrue);
        PalindromeProblem.LinkList<Integer> list1 = new PalindromeProblem.LinkList();
        list1.addAll(new Integer[]{1, 2, 2, 1});
        boolean test3 = palindromeProblem.way1LinkList(list1);
        Assert.assertTrue(test3);
        PalindromeProblem.LinkList<Integer> list2 = new PalindromeProblem.LinkList();
        list2.addAll(new Integer[]{1, 1, 1, 1, 1});
        boolean maybeTrue = palindromeProblem.way1LinkList(list2);
        Assert.assertTrue(maybeTrue);
        PalindromeProblem.LinkList<Integer> list3 = new PalindromeProblem.LinkList();
        list3.addAll(new Integer[]{1, 2, 3, 4, 5, 5, 4, 3, 2, 1});
        boolean mustTrue = palindromeProblem.way1LinkList(list3);
        Assert.assertTrue(mustTrue);
        PalindromeProblem.LinkList<Integer> list4 = new PalindromeProblem.LinkList();
        list4.addAll(new Integer[]{1, 2, 2, 2, 2, 2, 1});
        boolean test1 = palindromeProblem.way1LinkList(list4);
        Assert.assertTrue(test1);
        PalindromeProblem.LinkList<Integer> list5 = new PalindromeProblem.LinkList();
        list5.addAll(new Integer[]{1, 2, 5, 4, 3, 2, 3, 4, 5, 2, 1});
        boolean test2 = palindromeProblem.way1LinkList(list5);
        Assert.assertTrue(test2);
    }

}