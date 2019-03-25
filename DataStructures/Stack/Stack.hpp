#include "Stack.h"
#include <iostream>

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

CheckLegit::CheckLegit()
{
    stack = new Stack();
}

CheckLegit::~CheckLegit()
{
    delete stack;
}

CheckLegit::CheckLegit(std::vector<int> in_seq, std::vector<int> out_seq) : in_seq(in_seq), out_seq(out_seq)
{
    stack = new Stack();
}

bool CheckLegit::is_invalid()
{
    int index_in = 0, index_out = 0;

    while (index_in < in_seq.size() && index_out < out_seq.size())
    {
        while (index_in < in_seq.size() && (stack -> is_empty() || stack -> top() != out_seq[index_out]))
        {
            stack -> push(in_seq[index_in]);
            ++ index_in;
        }
        while (index_out < out_seq.size() && stack -> top() == out_seq[index_out])
        {
            stack -> pop();
            ++ index_out;
        }
    } 
    
    return stack -> is_empty();
}

Arrray_Stack::Arrray_Stack(int cap)
{
    capcity = cap;
    left_last  = -1;
    right_last = cap;
    array = new int[cap];
}

Arrray_Stack::Arrray_Stack()
{
    capcity = 10;
    left_last  = -1;
    right_last = 10;
    array = new int[10];
}

Arrray_Stack::~Arrray_Stack()
{
    delete array;
}

void Arrray_Stack::push(int flag, int value)
{
    if (check_capcity())
    {
        increase_capcity();
    }
    
    switch (flag)
    {
        case STACK1:
            ++ left_last;
            array[left_last] = value;
            break;
    
        case STACK2:
            -- right_last;
            array[right_last] = value;
            break;
        
        default :
            break;
    }
}

int Arrray_Stack::pop(int flag)
{
    if (is_empty(flag))
        return -1;
    
    int result = 0;
    
    switch (flag)
    {
        case STACK1:
            result = array[left_last --];
            break;

        case STACK2:
            result = array[right_last ++];
            break;

        default:
            break;
    }

    return result;
}

int Arrray_Stack::size(int flag)
{
    int size = 0;

    switch (flag)
    {
        case STACK1:
            size = left_last + 1;
            break;
        
        case STACK2:
            size = capcity - right_last + 1;
            break;
    
        default:
            break;
    }

    return size;
}

bool Arrray_Stack::is_empty(int flag)
{
    bool key = true;

    switch (flag)
    {
        case STACK1:
            key = (left_last == -1);
            break;
        
        case STACK2:
            key = (capcity == right_last);
            break;

        default:
            break;
    }

    return key;
}


bool Arrray_Stack::check_capcity()
{
    return (left_last + 1 == right_last); 
}

void Arrray_Stack::display()
{
    for (int i = 0; i < capcity; ++ i)
    {
        std::cout << array[i] << std::endl;
    }
}

void Arrray_Stack::increase_capcity()
{
    int origin_capcity = capcity;

    capcity *= 2;

    int* new_array = new int[capcity];

    for (int i = 0; i <= left_last; ++ i)
        new_array[i] = array[i];
    for (int i = origin_capcity - 1; i >= right_last; -- i)
        new_array[i + origin_capcity] = array[i];

    
    right_last += origin_capcity;
    delete array;
    array = new_array;
}