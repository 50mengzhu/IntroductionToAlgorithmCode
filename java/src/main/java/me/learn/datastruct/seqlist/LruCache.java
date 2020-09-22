package me.learn.datastruct.seqlist;

import java.util.Objects;

public class LruCache<T> {

    private static final Integer DEFAULT_CACHE_SIZE = 5;

    private SingleList<T> lruList;

    private int cacheSize;

    public LruCache() {
        this(DEFAULT_CACHE_SIZE);
    }

    public LruCache(int size) {
        cacheSize = size;
        lruList = new SingleList<>(size);
    }

    private void cache(T element) {
        Node hit = lruList.find(element);
        // no hit in cache
        if (hit == null) {
            if (lruList.size >= cacheSize) {
                // discard the tail element when cache size is full
                lruList.removeTail();
            }
            // add new element ahead
            lruList.addAhead(element);
        } else {
            lru(lruList, element);
        }
    }

    private void lru(SingleList<T> singleList, T element) {
        // remove old element
        lruList.remove(element);
        // add element ahead
        lruList.addAhead(element);
    }

    public void access(T element) {
        cache(element);
    }

    public void traveral() {
        lruList.traveral();
    }

    /**
     * single linked list for cache
     * provide
     * <i>add</i>
     * <i>remove</i>
     * <i>insert</i>
     */
    class SingleList<T> {

        int maxSize;

        int size = 0;

        private Node head;

        private Node originalHead;

        SingleList() {}

        SingleList(int size) {}

        boolean add(T element) {
            if (originalHead == null) {
                head = new Node(element);
                originalHead = head;
                // TODO concurrent
                ++ size;
                return true;
            }
            while (head != null) {
                head = head.next;
            }
            head = new Node(element);
            // TODO concurrent
            ++ size;
            return true;
        }

        private boolean insert(int index, T element) {
            // out of index
            if (index > size) {
                return false;
            }
            if (originalHead == null || index == size) {
                return add(element);
            }
            if (index == 0) {
                Node newHead = new Node(element);
                newHead.next = originalHead;
                originalHead = newHead;
                ++ size;
                return true;
            }
            Node tmp = originalHead;
            Node parent = new Node();
            while (index > 0 && tmp != null) {
                -- index;
                if (index == 0) {
                    parent = tmp;
                }
                tmp = tmp.next;
            }
            Node node = new Node(element);
            node.next = tmp;
            parent.next = node;
            ++ size;
            return true;
        }

        boolean addAhead(T element) {
            return insert(0, element);
        }

        private Node remove(int index) {
            if (index < 0 || index >= size) {
                return null;
            }
            Node tmp = originalHead;
            Node parent = new Node();
            while (index > 0 && tmp != null) {
                -- index;
                if (index == 0) {
                    parent = tmp;
                }
                tmp = tmp.next;
            }
            if (tmp == null) {
                parent.next = null;
            } else {
                parent.next = tmp.next;
                tmp.next = null;
            }
            -- size;
            return null;
        }

        public Node remove(T element) {
            Node tmp = originalHead;
            Node parent = new Node();
            while (tmp != null) {
                if (Objects.equals(element, tmp.data)) {
                    break;
                }
                parent = tmp;
                tmp = tmp.next;
            }
            if (tmp == null) {
                parent.next = null;
            } else {
                parent.next = tmp.next;
                tmp.next = null;
            }
            size --;
            return null;
        }

        Node removeTail() {
            return remove(size - 1);
        }

        Node find(T element) {
            Node tmp = originalHead;
            while (tmp != null) {
                if (Objects.equals(tmp.data, element)) {
                    return tmp;
                }
                tmp = tmp.next;
            }
            return null;
        }

        void traveral() {
            Node tmp = originalHead;
            while (tmp != null) {
                System.out.println(tmp.data);
                tmp = tmp.next;
            }
        }
    }

    class Node<T> {
        T data;
        Node next;

        Node() {}

        Node(T element) {
            this.data = element;
            this.next = null;
        }
    }
}
