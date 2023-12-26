#include "./SingleLinkedList.h"
#include <stdexcept>
namespace Ganesh
{
    template <typename T>
    inline SingleLinkedList<T>::SingleLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    template <typename T>
    void SingleLinkedList<T>::insertAtHead(T val)
    {
        Node<T> *newNode = new Node<T>(val);
        if (tail == nullptr)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }
    template <typename T>
    void SingleLinkedList<T>::insertAtTail(T val)
    {
        Node<T> *newNode = new Node<T>(val);
        if (tail == nullptr)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    template <typename T>
    void SingleLinkedList<T>::insertAt(T val, int idx)
    {
        if (idx < 0 || idx > size)
            throw std::out_of_range("index out of Range");
        if (idx == 0)
            insertAtHead(val);
        else if (idx == size)
            insertAtTail(val);
        else
        {
            Node<T> *newNode = new Node<T>(val);
            Node<T> *Current = head;
            for (int i{}; i < idx - 1; i++)
                Current->next = Current;
            newNode->next = Current->next;
            Current->next = newNode;
            size++;
        }
    }
    template <typename T>
    void SingleLinkedList<T>::pop()
    {
        if (size == 0)
            return;
        else if (size == 1)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node<T> *Current = head;
            while (Current->next != tail)
                Current = Current->next;
            delete tail;
            tail = Current;
            tail->next = nullptr;
        }
        size--;
    }
    template <typename T>
    void SingleLinkedList<T>::popAt(int idx)
    {
        if (idx < 0 || idx > size)
            throw std::out_of_range("index out of Range");
        if (idx == 0)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr)
                tail = nullptr;
        }
        else
        {
            Node<T> *Current = head;
            for (int i = 0; i < idx - 1; i++)
            {
                Current = Current->next;
            }
            Node<T> *temp = Current->next;
            Current->next = temp->next;
            delete temp;
            if (Current->next == nullptr)
                tail = Current;
        }
    }
    template <typename T>
    T &SingleLinkedList<T>::operator[](int idx)
    {
        if (idx < 0 || idx > size)
            throw std::out_of_range("index out of Range");
        Node<T> *Current = head;
        for (int i{}; i < idx - 1; i++)
            Current = Current->next;
        return Current->value;
    }
    template <typename T>
    int SingleLinkedList<T>::getSize() { return size; }
    template <typename T>
    inline SingleLinkedList<T>::~SingleLinkedList()
    {
        while (head != nullptr)
        {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
    }
    template <typename T>
    class SingleLinkedList<T>::Iterator
    {
    private:
        Node<T> *Current;

    public:
        Iterator(Node<T> *node) : Current(node) {}
        T &operator*() { return Current->data; }
        Iterator &operator++()
        {
            Current = Current->next;
            return *this;
        }
        bool operator!=(const Iterator &other) const
        {
            return Current != other.Current;
        }
    };
    template <typename T>
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::begin() { return Iterator(head); }
    template <typename T>
    typename SingleLinkedList<T>::Iterator SingleLinkedList<T>::end() { return Iterator(tail); }

}