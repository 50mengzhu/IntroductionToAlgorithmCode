#include <iostream>
#include "LinkList.h"

Node::Node()
{
    next = nullptr;
}

Node::Node(int val)
{
    data = val;
    next = nullptr;
}

Node::Node(Node* T)
{
    data = T -> data;
    next = T -> next;
}

Node::~Node()
{
    delete next;
}

LinkList::LinkList()
{ 
    head = nullptr;
}

LinkList::~LinkList()
{
    while (head != nullptr)
    {
        Node* temp = head -> next;
        delete head;
        head = temp;
    }
}

void LinkList::creatFront()
{
   int value;
   while (std::cin >> value)
   {
        Node* node = new Node(value);
        // node -> next = head -> next; 
        // head -> next = node;
        if (head == nullptr)
        {
            head = node;
            head -> next = nullptr;
        }
        else
        {
            node -> next = head;
            head = node;
        }
        
   }
}

void LinkList::creatRear()
{
    int value;
    while (std::cin >> value)
    {
        Node* node = new Node(value);
        if (head == nullptr)
        {
            head = node;
            rear = head;
        }
        else
        {
            node -> next = rear -> next;
            rear -> next = node;
            rear = node;
        }
    }
}

void LinkList::traverse()
{
    Node* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp -> data << std::endl;
        temp = temp -> next;
    }
    delete temp;
}

int LinkList::length()
{
    int length = 0;
    Node* temp = head;

    while (temp != nullptr)
    {
        ++ length;
        temp = temp -> next;
    }
    
    return length;
}

Node* LinkList::getHead()
{
    return head;
}

Node* Node::getNext()
{
    return next;
}

int Node::getValue()
{
    return data;
}

void Node::setNext(Node* node)
{
    next = node;
}


CircleList::CircleList()
{
    head = nullptr;
}

CircleList::~CircleList()
{
    Node* temp = head -> next;
    while (temp != head)
    {
        Node* temp_del = temp;
        delete temp_del;
        temp = temp -> next; 
    }
    delete temp;
}


void CircleList::creat()
{
    int value;
    Node* node, *p_head;

    while (std::cin >> value)
    {
        node = new Node(value);
        if (head == nullptr)
        {
            head = node;
            p_head = head;
        }
        else
        {
            p_head -> next = node;
            node -> next = head;
            p_head = node;
        }
    }
}

void CircleList::traverse()
{
    Node* temp = head -> next;

    std::cout << head -> data << std::endl;

    while (temp != head)
    {
        std::cout << temp -> data << std::endl;
        temp = temp -> next;
    }
}

Node* CircleList::getHead()
{
    return head;
}