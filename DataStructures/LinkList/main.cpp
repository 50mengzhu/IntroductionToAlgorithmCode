#include "LinkList.hpp"


int find_kth_num(LinkList* list, int k);
Node* revevrse_list(LinkList* list);
Node* revevrse_list_recursive(Node* root);

bool is_circle(Node* node);
int circle_length(Node* node);
Node* circle_enterance(Node* node);

int Josephus(LinkList* list);

int main()
{
/**** 创建无环单链表***/
    LinkList* list = new LinkList();

    // list -> creatFront();
    list -> creatRear();
    std::cin.clear();
    std::cin.sync();
    std::cin.ignore();
/**无环单链表结束**/

/****寻找无环单链表中倒数第k个结点***/
    // int k;
    // std::cout << "input k's value";
    
    // std::cin >> k;

    // std::cout << find_kth_num(list, k) << std::endl;
/****寻找结点结束****/

    // list -> traverse();

/****反转无环单链表****/
    // Node* head = revevrse_list(list);
    // Node* head = revevrse_list_recursive(list -> getHead());
/****反转结束*****/

    Node* head = list -> getHead();
    Node* temp = head;
    while (temp -> getNext() != nullptr)
    {
        std::cout << temp -> getValue() << std::endl;
        temp = temp -> getNext();
    }

/***创建循环链表*****/
    CircleList *cList = new CircleList();
    cList -> creat();
    // cList -> traverse();
/***循环链表结束*****/

    temp -> setNext(cList -> getHead());
    std::cout << "---------------";
    std::cout << is_circle(head) << std::endl;
    std::cout << circle_length(head) << std::endl;
    std::cout << circle_enterance(head) -> getValue() << std::endl;

    return 0;
}


/**
 * 来源：剑指offer
 * 描述：求链表中的倒数第k个结点
 * 思路：使用前后指针法（前一个指针比后一个指针快k个），当后面的指针走到链表尾的时候，第一个指针所指的就是答案
*/
int find_kth_num(LinkList* list, int k)
{
    if (list == nullptr || list -> length() < k)
    {
        return -1;
    }

    Node* pre_pt = list -> getHead();

    int i = 0;
    for (; i < k - 1; ++ i)
    {
        pre_pt = pre_pt -> getNext();
    }

    Node* post_pt = list -> getHead();

    while (pre_pt -> getNext() != nullptr)
    {
        pre_pt = pre_pt -> getNext();
        post_pt = post_pt -> getNext();
    }

    return post_pt -> getValue();
}

/**
 * 来源：笔试题
 * 描述：输入一个头结点，反转该链表并输出该链表的头结点
 * 思路：1、O(n)时间和O(n)空间的常规算法——使用栈存放链表中的数据，然后依次将数字出栈赋值给原链表。但是耗费了多余的空间
 * 2、O(n)时间和原地更换，使用三个指针来完成，具体原理见同目录下的md文件
 * 
*/
Node* revevrse_list(LinkList* list)
{
    if (list == nullptr)
    {
        return nullptr;
    }

    Node* first_pt = nullptr, *second_pt = list -> getHead(), *third_pt = nullptr;

    while (second_pt != nullptr)
    {
        third_pt = second_pt -> getNext();
        second_pt -> setNext(first_pt);
        first_pt = second_pt;
        second_pt = third_pt;
 
    }

    return first_pt;
}

Node* revevrse_list_recursive(Node* root)
{
    Node* rootNode;
    if (root == nullptr || root -> getNext() == nullptr)
    {
        return root;
    }
    rootNode = revevrse_list_recursive(root -> getNext());

    root -> getNext() -> setNext(root);
    root -> setNext(nullptr);

    return rootNode;
}

/**
 * 来源：面试题
 * 描述：判断但链表是否成环
 * 思路：快慢指针法，追赶问题的实际应用
 * **/
bool is_circle(Node* node)
{
    Node* fast_pt = node;
    Node* slow_pt = fast_pt;

    while (fast_pt != nullptr || fast_pt -> getNext() != nullptr)
    {
        fast_pt = fast_pt -> getNext() -> getNext();
        slow_pt = slow_pt -> getNext();
        if (fast_pt == nullptr || fast_pt -> getNext() == nullptr)
                break;
        if (fast_pt == slow_pt)
        {
            return true;
        }
    }
    
    return false;
}

/**
 * 来源：面试题
 * 描述：判断链表是否有环，并再次基础上判断环的长度
 * 思路：这就是我们在数学中常遇到得追及问题，从第一次相遇到第二次相遇，快慢指针得移动差就是环得长度
 * *****/
int circle_length(Node* node)
{
    if (!is_circle(node))
    {
        return 0;
    }

    Node* fast_pt = node;
    Node* slow_pt = node;
    int length = 0;

    bool begin = false;
    bool again = false;

    while (fast_pt != nullptr || fast_pt -> getNext() != nullptr)
    {
        fast_pt = fast_pt -> getNext() -> getNext();
        slow_pt = slow_pt -> getNext();

        if (fast_pt == slow_pt && again)
            break;

        if (fast_pt == slow_pt && !again)
        {
            again = true;
            begin = true;
        }    

        if (begin)
            ++ length;     
    }
    
    return length;
}

/****
 * 来源：笔试题
 * 描述：判断链表是否有环，如果有，请返回该环的入口结点
 * 思路：见本章的md
 * **/
Node* circle_enterance(Node* node)
{
    if (node == nullptr)
        return nullptr;
    
    Node* fast_pt = node;
    Node* slow_pt = fast_pt;
    Node* meet_pt = new Node();
    bool  key = false;

    while (fast_pt != nullptr || fast_pt -> getNext() != nullptr)
    {
        fast_pt = fast_pt -> getNext() -> getNext();
        slow_pt = slow_pt -> getNext();

        if (fast_pt == nullptr || fast_pt -> getNext() == nullptr)
            break;
        
        if (fast_pt == slow_pt)
        {
            key = true;
            break;
        }
    }

    if (!key)
    {
        return nullptr;
    }
    else
        meet_pt = fast_pt;

    Node* head = node;
    while (meet_pt != head)
    {
        meet_pt = meet_pt -> getNext();
        head = head -> getNext();
    }

    return meet_pt;
}




/**
 * https://blog.csdn.net/thefutureisour/article/details/8174313
 * http://wemedia.ifeng.com/73680917/wemedia.shtml
 * https://github.com/chankeh/cpp-backend-reference/blob/master/back-end.md
 * **/