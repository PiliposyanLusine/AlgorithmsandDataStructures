#include <iostream>

class Stack
{
    private:
        int* arr;
        int capacity;
        int top;
    
    public:
        Stack(int initCapacity = 10)
        {
            capacity = initCapacity;
            arr = new int[capacity];
            top = -1;
        }

        ~Stack()
        {
            delete[] arr;
        }

        bool empty() const
        {
            return top == -1;
        }

        void push(int value)
        {   
            if(top == capacity - 1)
            {
                int* newArr = new int[capacity * 2];
                for(int i = 0; i <= top; ++i)
                {
                    newArr[i] = arr[i];
                }
                delete[] arr;
                arr = newArr;
                capacity *= 2; 
            }
            arr[++top] = value;
        }

        void pop()
        {
            if(empty())
            {
                std::cout << "Stack is empty. Cannot pop" << std::endl;
                return;
            }
            --top;
        }

        int size() const
        {
            return top + 1;
        }
};

int main() 
{
    Stack stack;

    std::cout << "Pushing elements onto the stack:" << std::endl;
    for (int i = 1; i <= 10; ++i) 
    {
        stack.push(i);
        std::cout << "Pushed " << i << ", Size: " << stack.size() << std::endl;
    }

    std::cout << "Popping elements from the stack:" << std::endl;
    while (!stack.empty()) 
    {
        std::cout << "Popped " << stack.size() << ", Size: " << stack.size() << std::endl;
        stack.pop();
    }

    return 0;
}
