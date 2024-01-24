#include <iostream>

class Node
{
public:
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr){}
};

class LinkedList
{   
    private:
        Node* head;
        int size;
    public:
        LinkedList() : head(nullptr), size(0) {}

        void insert(int value, int position)
        {
            if(position < 0 || position > size)
            {
                std::cerr << "Invalid position for insertion " << std::endl;
                return;
            }
            Node* newNode = new Node(value);
            if(position == 0)
            {
                newNode->next = head;
                head = newNode;
            }
            else
            {
                Node* current = head;
                for(int i = 0; i < position - 1; ++i)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
            ++size;
        }


        void clear()
        {
            while (head != nullptr)
            {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            size = 0;
        }

        void push_back(int value)
        {
            insert(value, size);
        }


        void pop_back()
        {
            remove(size - 1);
        }


        void reverse() 
        {
            Node* prev = nullptr;
            Node* current = head;
            Node* nextNode = nullptr;

            while (current) 
            {
                nextNode = current->next;
                current->next = prev;
                prev = current;
                current = nextNode;
            }

            head = prev;
        }

        void remove(int position)
        {
            if(position < 0 || position > size)
            {
                std::cerr << "Invalid position for removal" << std::endl;
                return;
            }

            if(position == 0)
            {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            else
            {   
                Node* current = head;
                for(int i = 0; i < position; ++i)
                {
                    current = current->next;
                }
                Node* tmp = current->next;
                current->next = tmp->next;
                delete tmp;
            }
            size--;
        }

        int get_size() const
        {
            return size;
        }


        static LinkedList merge(LinkedList& list1, LinkedList& list2) 
        {
            LinkedList mergedList;
            Node* current1 = list1.head;
            Node* current2 = list2.head;

            while (current1 && current2) 
            {
                if (current1->data < current2->data) 
                {
                    mergedList.push_back(current1->data);
                    current1 = current1->next;
                } 
                else 
                {
                    mergedList.push_back(current2->data);
                    current2 = current2->next;
                }
            }

            while (current1) 
            {
                mergedList.push_back(current1->data);
                current1 = current1->next;
            }

            while (current2) 
            {
                mergedList.push_back(current2->data);
                current2 = current2->next;
            }

            return mergedList;
        }
};

int main() 
{
    LinkedList list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    std::cout << "List size: " << list.get_size() << std::endl;

    list.insert(5, 2);
    list.remove(3);

    std::cout << "List size after modifications: " << list.get_size() << std::endl;

    list.clear();

    std::cout << "List size after clear: " << list.get_size() << std::endl;

    return 0;
}
