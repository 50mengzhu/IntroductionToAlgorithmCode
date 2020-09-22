package me.learn.datastruct.seqlist;

import java.util.Objects;
import java.util.Stack;

/**
 * palindrome problem:
 *
 * judge a string is palindrome or not
 * some times we use array to solve this,
 * but we now using list
 *
 * @param <T>
 * @author mica
 */
public class PalindromeProblem<T> {

    public boolean palindromeString (String str) {

        return false;
    }


    // ------------ using array to store data ------------

    /**
     * using stack to reserve original string
     * then pop it and compare to original string
     *
     * Time complexity: O(n)
     *      first we need to push all elements to stack. which need O(n)
     *      then we compare stack and original string which need to calculate is O(n), too
     *      so O(n) + O(n)
     * Spatial complexity: O(n)
     *      using a extra stack, so the Spatial complexity is O(n)
     *
     * @param str   original string
     * @return  true for String is Palindrome;
     *          false is not Palindrome
     */
    public boolean way1String(String str) {
        Stack<Character> stack = new Stack<>();
        for (char s : str.toCharArray()) {
            stack.push(s);
        }
        int i = 0;
        while (!stack.isEmpty()) {
            if (Objects.equals(stack.pop(), str.charAt(i))) {
                ++ i;
                continue;
            } else {
                return false;
            }
        }
        return true;
    }


    /**
     * using to position pointer: one is from start to end,
     * while the other is from end to start. So just compare
     * the two position's element, if they all the same, then str
     * is the Palindrome.
     *
     * Time complexity: O(n)
     *      we just compare stack and original string which need to calculate is O(n/2)
     * Spatial complexity: O(1)
     *      no extra Spatial cost
     *
     * @param str   original string
     * @return true for String is Palindrome;
     *         false is not Palindrome
     */
    public boolean way2String(String str) {
        int start = 0;
        int end = str.length() - 1;
        while (start <= end) {
            if (Objects.equals(str.charAt(start), str.charAt(end))) {
                ++ start;
                -- end;
                continue;
            } else {
                return false;
            }
        }
        return true;
    }


    // ------------ using link list to store data
    // ------------ define of Link list

    static class Node<T> implements Cloneable {
        T data;
        Node next;

        Node(T data) {
            this.data = data;
            this.next = null;
        }

        @Override
        protected Object clone()
                throws CloneNotSupportedException {
            return super.clone();
        }
    }

    public static class LinkList<T> {

        private Node head;

        private Node originalHead;

        private int size = 0;

        boolean addAll(T[] arrays) {
            if (originalHead == null) {
                head = new Node(arrays[0]);
                originalHead = head;
                ++ size;
            }
            while (head.next != null) {
                head = head.next;
            }
            for (int i = 1; i < arrays.length; ++ i) {
                Node node = new Node(arrays[i]);
                head.next = node;
                head = node;
                ++ size;
            }
            return true;
        }

        public Node getHead() throws CloneNotSupportedException {
            return (Node) this.originalHead.clone();
        }

        public int getSize() {
            return this.size;
        }

        public void clear() {
            Node tmp = originalHead;
            while (tmp != null) {
                tmp.next = null;
                tmp.data = 0;
                tmp = tmp.next;
                -- size;
            }
            assert size == 0;
            size = 0;
        }
    }

    /**
     * judge an linklist is Palindrome or not
     *
     * @param list
     * @return
     */
    @SuppressWarnings("unchecked")
    public boolean way1LinkList(LinkList<T> list) throws CloneNotSupportedException {
        // fast-slow pointer to find the center of list
        Node head = list.getHead();
        Node fastPointer = head;
        Node slowPointer = head;
        Node son = null;
        Node currentNode = head;
        Node node = head;

        // using fast and slow pointer have 2 advantages:
        // 1. to find the center of link list
        // 2. to reverse left list before center
        while (fastPointer != null && fastPointer.next != null) {
            fastPointer = fastPointer.next.next;
            slowPointer = slowPointer.next;
        }

        // reverse link list
        // exactly reverse the first half of list OR reverse the second half of list
        // can reach the same goal, but if we reserve the first we need to cation about
        // size of list, when its size is even we use this; while its size is odd
        // we need to take slow point to the next.
        // Things may be easy when we reserve the second part, because this way we got the slow
        // point be the last node that both first-half list and the reserve-second-half list
        while (node != slowPointer) {
            currentNode = node;
            node = node.next;
            currentNode.next = son;
            son = currentNode;
        }

        if (list.getSize() % 2 != 0) {
            slowPointer = slowPointer.next;
        }
        while (slowPointer != null) {
            if (!Objects.equals(slowPointer.data, son.data)) {
                return false;
            }
            slowPointer = slowPointer.next;
            son = son.next;
        }
        return true;
    }





}
