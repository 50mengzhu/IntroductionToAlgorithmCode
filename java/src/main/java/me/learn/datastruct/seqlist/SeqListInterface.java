package me.learn.datastruct.seqlist;

/**
 * an interface for sequential list
 * define what common operations that seq-list can do
 * <strong>array</strong><strong>Single/Circle/Doubly LinkedList</strong> are all the implements
 * of this class. But what i implements is just LinkedList
 * <p>
 * BTW, i will using my data struct to solve server problem
 *
 * @author mica
 */
public interface SeqListInterface <T> {

    /**
     * add an element to the SeqList
     *
     * @param element  element to added
     * @return  true when it was added successfully,
     *          otherwise return false
     */
    boolean add(T element);

    /**
     * remove an element which is specified by param
     *
     * @param element   element to be removed
     * @return  element entity when is was remove successfully;
     *          otherwise return null
     */
    T remove(T element);
}
