#include "Queue.h"

Node::Node()
{
    next = nullptr;
}

Node::Node(int value)
{
    data = value;
    next = nullptr;
}

Node::~Node()
{
    delete next;
}

Queue::Queue()
{
    head   = nullptr;
    length = 0;
}

Queue::~Queue()
{
    delete head;
}

void Queue::push(int value)
{
    Node* node = new Node(value);

    if (head == nullptr)
    {
        head = node;
        rear = head;
        ++ length;
    }
    else
    {
        rear -> next = node;
        rear = node;
        ++ length;
    }
}

int Queue::pop()
{
    if (length == 0)
        return -1;
    
    int result = head -> data;
    head = head -> next;
    -- length;

    return result;
}

int Queue::front()
{
    return head -> data;
}

int Queue::back()
{
    return rear -> data;
}

int Queue::size()const
{
    return length;
}

bool Queue::is_empty()
{
    return !length;
}


Stack_By_Queue::Stack_By_Queue()
{
    in_queue  = new Queue();
    out_queue = new Queue();
}

Stack_By_Queue::~Stack_By_Queue()
{
    delete in_queue;
    delete out_queue;
}

void Stack_By_Queue::push(int value)
{
    in_queue -> push(value);
}

int Stack_By_Queue::pop()
{
    int result = -1;
    int len = 0;
    if (is_empty())
        return result;
    
    if (out_queue -> is_empty())
    {
        len = in_queue -> size();
        while (len > 1)
        {
            out_queue -> push(in_queue -> pop());
            -- len;
        }
        result = in_queue -> pop();
    }
    else if (!(out_queue -> is_empty()))
    {
        len = out_queue -> size();
        while (len > 1)
        {
            in_queue -> push(out_queue -> pop());
            -- len;
        }
        result = out_queue -> pop();
    }

    return result;
}

int Stack_By_Queue::size() const
{
    return in_queue -> size() + out_queue -> size();
}

bool Stack_By_Queue::is_empty()
{
    return !(in_queue -> size() + out_queue -> size());
}

void Stack_By_Queue::clear()
{
    while (!(in_queue -> is_empty()))
        in_queue -> pop();
    while (!(out_queue -> is_empty()))
        out_queue -> pop();
}

int Stack_By_Queue::top()
{
    int len = 0;
    if (is_empty())
        return -1;
    
    if (out_queue -> is_empty())
    {
        len = in_queue -> size();
        while (len > 1)
        {
            out_queue -> push(in_queue -> pop());
            -- len;
        }
        return in_queue -> front();
    }

    if (!(out_queue -> is_empty()))
    {
        len = out_queue -> size();
        while (len > 1)
        {
            in_queue -> push(out_queue -> pop());
            -- len;
        }
        return out_queue -> front();
    }

    return 0;
}

