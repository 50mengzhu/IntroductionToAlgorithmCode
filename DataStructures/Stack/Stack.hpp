#include "Stack.h"

Node::Node()
{
    next = nullptr;
}

Node::Node(int value)
{
    data = value;
    next = nullptr;
}

Stack::Stack()
{
    head = nullptr;
    length = 0;
}

Stack::~Stack()
{
    clear();
}

void Stack::push(int data)
{
    Node* node = new Node(data);

    if (head == nullptr)
    {
        head = node;
        ++ length;
    }
    else
    {
        node -> next = head;
        head = node;
        ++ length;
    }
}

int Stack::pop()
{
    if (head == nullptr)
    {
        return -1;
    }
    int value = head -> data;
    head = head -> next;
    -- length;

    return value;
}

int Stack::top()
{
    if (head == nullptr)
    {
        return -1;
    }

    return head -> data;
}

int Stack::size()
{
    return length;
}

void Stack::clear()
{
    while (head != nullptr)
        pop();
}

bool Stack::is_empty()
{   
    return !length;
}


Queue::Queue()
{
    head = nullptr;
    rear = nullptr;
    length = 0;
}

Queue::~Queue()
{
    while(!is_empty())
    {
        pop();
    }
    
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
        rear -> next = nullptr;
        ++ length;
    }
}

int Queue::pop()
{
    if (is_empty())
    {
        return -1;
    }
    int value = head -> data;
    -- length;
    head = head -> next;
    return value;
}

int Queue::front()
{
    if (is_empty())
    {
        return -1;
    }
    return head -> data;
}

bool Queue::is_empty()
{
    return !length;
}

int Queue::size()
{
    return length;
}



MinStack::MinStack()
{
    Stack();
}

int MinStack::find_min()
{
    return top();
}

MinStack::~MinStack(){}

void MinStack::_push(int value)
{
    if (is_empty())
    {
        push(value);
        push(value);
        Min = value;
    }
    else
    {
        push(value);
        Min = value > Min ? Min : value;
        push(Min);
    }
}

MinStack_Two::MinStack_Two()
{
    normal_stack = new Stack();
    min_stack = new Stack();
}

MinStack_Two::~MinStack_Two(){}

void MinStack_Two::push(int value)
{
    if (normal_stack -> is_empty() && min_stack -> is_empty())
    {
        normal_stack -> push(value);
        min_stack -> push(value);
    }
    else
    {
        int min = min_stack -> top();

        normal_stack -> push(value);
        min = value > min ? min : value;
        min_stack -> push(min);
    }
}

int MinStack_Two::get_Min()
{
    if (!(min_stack -> is_empty()))
        return min_stack -> top();
    else
        return -1;
}

int MinStack_Two::pop()
{
    if (!(normal_stack -> is_empty()) && !(min_stack -> is_empty()))
    {
        min_stack -> pop();
        return normal_stack -> pop();
    }
    else 
        return -1;
}


Queue_By_Stack::Queue_By_Stack()
{
    in_stack = new Stack();
    out_stack = new Stack();
}

Queue_By_Stack::~Queue_By_Stack()
{
    if (is_empty())
    {
        pop();
    }
}

void Queue_By_Stack::push(int value)
{
    in_stack -> push(value);
}

int Queue_By_Stack::pop()
{
    if (is_empty())
        return -1;
    
    if (out_stack -> is_empty())
    {
        while (!(in_stack -> is_empty()))
        {
            out_stack -> push(in_stack -> pop());
        }
    }

    return out_stack -> pop();  
}

int Queue_By_Stack::front()
{
    if (is_empty())
        return -1;
    
    if (out_stack -> is_empty())
    {
        while (!(in_stack -> is_empty()))
        {
            out_stack -> push(in_stack -> pop());
        }
    }
        
    return out_stack -> top();
}

bool Queue_By_Stack::is_empty()
{
    return !(in_stack -> size() + out_stack -> size());
}

int Queue_By_Stack::size()
{
    return in_stack -> size() + out_stack -> size();
}