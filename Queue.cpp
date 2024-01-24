#include <iostream>

class Queue
{
    private:
        int* arr;
        static const int defaultCapacity = 100;
        int front;
        int rear;
    public:
        Queue()
        {
            arr = new int[defaultCapacity];
        }
        void enqueue(int element)
        {
            arr[rear++] = element;
        }
  
  
  
        int dequeue()
        {
            if(rear < front)
            {
                std::cout << "error" << std::endl;
                return 0;
            }
            else
            {
                return arr[front++];
            }
        }

        int getFront()
        {
            if(!isEmpty())
            {
                return -1;
            }
            else
            {
                return arr[front];
            }
        }


        int getRear()
        {
                        if(!isEmpty())
            {
                return -1;
            }
            else
            {
                return arr[rear];
            }            
        }


        bool isEmpty()
        {
            return rear<front;
        }
};


int main()
{
    Queue queue;
}