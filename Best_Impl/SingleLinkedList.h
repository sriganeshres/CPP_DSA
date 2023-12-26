#ifndef SINGLELINKEDLIST_H_
#define SINGLELINKEDLIST_H_
namespace Ganesh
{
    template <typename T>
    struct Node
    {
        T value;
        Node *next;
        Node() : value(0), next(nullptr) {}
        Node(T &v) : value(v), next(nullptr) {}
    };
    template <typename T>
    class SingleLinkedList
    {
    private:
        Node<T> *head, *tail;
        int size;

    public:
        SingleLinkedList();
        void insertAtHead(T val);
        void insertAtTail(T val);
        void insertAt(T val, int idx);
        void pop();
        void popAt(int idx);
        T &operator[](int idx);
        int getSize();
        ~SingleLinkedList();
        class Iterator;
        Iterator begin();
        Iterator end();
    };
}
#endif