#include <iostream>
#include <string>
#define N INT16_MAX
class Stack
{
private:
    int *arr, top;

public:
    Stack()
    {
        arr = new int[N];
        top = -1;
    }
    void Push(int x)
    {
        arr[++top] = x;
    }
    void Pop()
    {
        if (top < 0)
        {
            std::cout << "stack is empty\n";
            return;
        }
        else
        {
            top--;
        }
    }
    bool isEmpty()
    {
        if (top < 0)
            return true;
        return false;
    }
    int Peek()
    {
        if (top < 0)
            return -1;
        return arr[top];
    }
    int Size()
    {
        return top + 1;
    }
};
int main()
{
    Stack S;
    int num, i = 0;
    std::cin >> num;
    while (i < num)
    {
        std::string input;
        std::cin >> input;
        if (input == "push")
        {
            int x;
            std::cin >> x;
            S.Push(x);
        }
        else if (input == "pop")
        {
            S.Pop();
        }
        else if (input == "isempty")
        {
            std::cout << S.isEmpty() << '\n';
        }
        else if (input == "peek")
        {
            std::cout << S.Peek() << '\n';
        }
        else if (input == "size")
        {
            std::cout << S.Size() << '\n';
        }
        i++;
    }
}