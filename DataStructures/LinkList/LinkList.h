class LinkList;

class Node{
    friend class LinkList;
    friend class CircleList;
    private:
        int     data;
        Node*   next;
    public:
        Node();
        Node(int val);
        Node(Node* T);
        ~Node();
        Node* getNext();
        int getValue();
        void setNext(Node*);
};

class LinkList
{
private:
    Node* head;
    Node* rear;
public:
    LinkList();
    ~LinkList();

    int  length();
    void creatFront();
    void creatRear();
    void traverse();
    Node* getHead();
};

class CircleList
{
private:
    Node* head;
public:
    CircleList();
    ~CircleList();

    void creat();
    void traverse();
    Node* getHead();
};
