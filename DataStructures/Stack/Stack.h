class Stack;
#include <vector>

class Node
{
friend class Stack;
friend class Queue;
private:
    int data;
    Node* next;
public:
    Node();
    Node(int value);
    ~Node();
};

class Stack
{
public:
    int length;
    Node* head;

protected:
    Node* setHead(Node* node);
    void setLength(int length);

public:
    Stack(/* args */);
    ~Stack();

    void push(int data);
    int pop();
    bool is_empty();
    int size();
    int top();
    void clear();   
    // void traverse();
};


class Queue
{
private: 
    Node *head;
    int length;
    Node* rear;

public:
    Queue();
    ~Queue();
    void push(int value);
    int  pop();
    int  front();
    int  back();
    int  size();
    bool is_empty();
};


/***
 * 来源：面试题
 * 描述：创建一个栈，使得push、pop以及取得栈中最小值的时间均为O(1)
 * 思路：由于栈的push和pop本来就是O(1)的操作，因此只需要涉及最小值为O(1)即可
 *      总之就是，用空间换取时间
 * -----------------
 * 下面是采用一个栈完成
 * -----------------
 * ****/
class MinStack : public Stack
{
private:
    int Min;
public:
    MinStack();
    ~MinStack();

    void _push(int value);
    
    int find_min();
};


/***
 * 来源：
 * 描述：使得push、pop以及取得栈中最小值的时间均为O(1)
 * 思路：空间换时间，
 * ----------------
 * 以下是使用两个栈实现
 * ----------------
 * ***/
class MinStack_Two
{
private:
    Stack* normal_stack;
    Stack* min_stack;

public:
    MinStack_Two();
    ~MinStack_Two();

    void push(int value);
    int pop();
    int get_Min();
};


/***
 * 来源：经典面试题
 * 描述：使用两个栈实现一个队列
 * 思路：有两种思路，一种思路就是将所有的数据全部放在一个栈中
 * 还有一种思路就是将数据分别放在不同的栈中，分别充当输入栈和输出栈
 * ***/
class Queue_By_Stack
{
private: 
    Stack* in_stack;
    Stack* out_stack;

public: 
    Queue_By_Stack();
    ~Queue_By_Stack();
    void push(int value);
    int  pop();
    int  front();
    bool is_empty();
    int  size();
};

/***
 * 来源：经典面试题
 * 描述：已知一个入栈序列，判断出栈序列是否合法
 * 思路：整体上就是模拟序列入栈出栈的方式，采用两个vector和一个辅助栈来进行模拟操作
 * **/

class CheckLegit
{
private:
    std::vector<int> in_seq;
    std::vector<int> out_seq;
    Stack* stack;

public:
    CheckLegit();
    ~CheckLegit();
    CheckLegit(std::vector<int> in_seq, std::vector<int> out_seq);

    bool is_invalid();
};


/****
 * 来源：经典面试题
 * 描述：使用一个数组实现两个栈，使得只要数组还有空间就能入栈成功
 * 思路：详细见附件md中的分析
 * ***/
#define STACK1 0
#define STACK2 1

class Arrray_Stack
{
private:
    int* array;
    int left_last;
    int right_last;
    int capcity;

public:
    Arrray_Stack();
    Arrray_Stack(int capcity);
    ~Arrray_Stack();

    void increase_capcity();
    void push(int flag, int value);
    int  pop(int flag);
    int  size(int flag);
    bool is_empty(int flag);
    bool check_capcity();
    void display();
};