package me.learn.datastruct.seqlist;

import java.util.Objects;

/**
 *
 * @author mica
 */
public class SingleLinkedList<T> implements SeqListInterface<T> {

    class Node {
        T data;
        Node nextNode;

        Node() {}

        Node(T element) {
            data = element;
            nextNode = null;
        }
    }

    private Node head;
    private Node originHead;
    private int size;

    @Override
    public boolean add(T element) {
        if (head == null) {
            head = new Node(element);
            originHead = head;
            size ++;
            return true;
        }
        while (head.nextNode != null) {
            head = head.nextNode;
        }
        Node node = new Node(element);
        head.nextNode = node;
        size ++;
        return true;
    }

    public boolean addAll(T[] elements) {
        if (head == null) {
            head = new Node(elements[0]);
            originHead = head;
            size ++;
        }
        while (head.nextNode != null) {
            head = head.nextNode;
        }
        for (int i = 1; i < elements.length; ++ i) {
            head.nextNode = new Node(elements[i]);
            head = head.nextNode;
            size ++;
        }
        return true;
    }

    public Node contains(T element) {
        Node tmp = originHead;
        while (tmp != null) {
            if (Objects.equals(element, tmp.data)) {
                return tmp;
            }
            tmp = tmp.nextNode;
        }
        return null;
    }

    public void traversal() {
        Node tmp = originHead;
        while (tmp != null) {
            System.out.println(tmp.data);
            tmp = tmp.nextNode;
        }
    }

    public int size() {
        return this.size;
    }

    @Override
    public T remove(T element) {
        return null;
    }
}
