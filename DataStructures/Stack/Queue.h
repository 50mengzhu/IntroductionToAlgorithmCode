class Stack;

class Node
{
friend class Queue;
private:
    int data;
    Node* next;
public:
    Node();
    Node(int value);
    ~Node();
};

class Queue
{
private:
    int     length;
    Node*   head;
    Node*   rear;
public:
    Queue();
    ~Queue();

    void push(int value);
    int  pop();
    int  front();
    int  back();
    int  size()const;
    bool is_empty();
};

class Stack_By_Queue
{
private: 
    Queue* in_queue;
    Queue* out_queue;
public: 
    Stack_By_Queue();
    ~Stack_By_Queue();
    
    void push(int value);
    int  pop();
    int  top();
    int  size()const;
    bool is_empty();
    void clear();
};
