#include <iostream>

template <typename T>
class Node 
{
    public:
        T data;
        Node* next;
        Node* prev;
        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList 
{
    private:
        Node<T>* head;
        Node<T>* tail;
        int length;

    public:
        DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

        Node<T>* getHead() const 
        {
            return head;
        }

        Node<T>* getTail() const 
        {
            return tail;
        }

        Node<T>* getTail(Node<T>* listHead) 
        {
            if (!listHead) 
            {
                return nullptr;
            }

            Node<T>* tail = listHead;
            while (tail->next) 
            {
                tail = tail->next;
            }

            return tail;
        }

        void push_back(T value) 
        {
            Node<T>* newNode = new Node<T>(value);
            if (!tail) 
            {
                head = tail = newNode;
            } 
            else 
            {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            length++;
        }

        void push_front(T value) 
        {
            Node<T>* newNode = new Node<T>(value);
            if (!head) 
            {
                head = tail = newNode;
            } 
            else 
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            length++;
        }

        void pop_back() 
        {
            if (!tail) 
            {
                return;
            }
            Node<T>* temp = tail;
            tail = tail->prev;
            if (!tail) 
            {
                head = nullptr;
            } 
            else 
            {
                tail->next = nullptr;
            }
            delete temp;
            length--;
        }

        void pop_front() 
        {
            if (!head) 
            {
                return;
            }
            Node<T>* temp = head;
            head = head->next;
            if (!head) 
            {
                tail = nullptr;
            } 
            else 
            {
                head->prev = nullptr;
            }
            delete temp;
            length--;
        }


        void erase(int position) 
        {
            if (position < 0 || position >= length) 
            {
                return;
            }
            if (position == 0) 
            {
                pop_front();
            } 
            else if (position == length - 1) 
            {
                pop_back();
            } 
            else 
            {
                Node<T>* current = head;
                for (int i = 0; i < position; i++) 
                {
                    current = current->next;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                length--;
            }
        }


        void insert(int position, T value) 
        {
            if (position < 0 || position > length) 
            {
                return;
            }
            if (position == 0) 
            {
                push_front(value);
            } 
            else if (position == length) 
            {
                push_back(value);
            } 
            else 
            {
                Node<T>* newNode = new Node<T>(value);
                Node<T>* current = head;
                for (int i = 0; i < position; i++) 
                {
                    current = current->next;
                }
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev->next = newNode;
                current->prev = newNode;
                length++;
            }
        }

        void clear() 
        {
            while (!empty()) 
            {
                pop_front();
            }
        }


        bool empty() const 
        {
            return length == 0;
        }


        int size() const 
        {
            return length;
        }


        void reverse() 
        {
            if (length <= 1) 
            {
                return;
            }
            Node<T>* current = head;
            while (current) 
            {
                Node<T>* temp = current->next;
                current->next = current->prev;
                current->prev = temp;
                if (temp) 
                {
                    tail = head;
                    head = current;
                } 
                else 
                {
                    head->prev = nullptr;
                    tail->next = nullptr;
                }
                current = temp;
            }
        }



        template <typename T>
        Node<T>* reverseDoublyLinkedList(Node<T>* head) 
        {
            if (!head) {
                return nullptr; 
            }
            Node<T>* current = head;
            Node<T>* newHead = nullptr;
            while (current != nullptr) 
            {
                Node<T>* temp = current->next;
                current->next = current->prev;
                current->prev = temp;
                newHead = current;
                current = temp;
            }

            return newHead; 
        }





        Node<T>* getMiddleNode(Node<T>* head) 
        {
            if (head == nullptr || head->next == nullptr) 
            {
                return head;
            }
            Node<T>* slow = head;
            Node<T>* fast = head;
            while (fast->next && fast->next->next ) 
            {
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        }


        std::pair<bool, Node<T>*> detectCycleAndGetStartPoint(Node<T>* head)
        {
            Node<T>* slow = head;
            Node<T>* fast = head;
            while (fast && fast->next ) 
            {
                slow = slow->next;
                fast = fast->next->next;
                if (slow == fast) 
                {
                    Node<T>* start = head;
                    while (start != slow) 
                    {
                        start = start->next;
                        slow = slow->next;
                    }
                    return std::make_pair(true, start);
                }
            }
            return std::make_pair(false, nullptr);
        }




        std::pair<Node<T>*, Node<T>*> mergeTwoSortedLinkedLists(Node<T>* list1, Node<T>* list2) 
        {
            if (!list1) 
            {
                return {list2, getTail(list2)};
            }
            if (!list2) 
            {
                return {list1, getTail(list1)};
            }

            Node<T>* result = nullptr;
            Node<T>* tail = nullptr;

            while (list1 && list2) 
            {
                if (list1->data <= list2->data) 
                {
                    if (!result) 
                    {
                        result = tail = list1;
                    } 
                    else 
                    {
                        tail->next = list1;
                        list1->prev = tail;
                        tail = list1;
                    }
                    list1 = list1->next;
                } 
                else 
                {
                    if (!result) 
                    {
                        result = tail = list2;
                    } 
                    else 
                    {
                        tail->next = list2;
                        list2->prev = tail;
                        tail = list2;
                    }
                    list2 = list2->next;
                }
            }

            if (list1) 
            {
                tail->next = list1;
                list1->prev = tail;
                tail = getTail(list1);
            } 
            else if (list2) 
            {
                tail->next = list2;
                list2->prev = tail;
                tail = getTail(list2);
            }

            return {result, tail};
        }

        void merge(DoublyLinkedList<T>& other) 
        {
            auto mergedResult = mergeTwoSortedLinkedLists(head, other.head);
            head = mergedResult.first;
            tail = mergedResult.second;
            length += other.size();
            other.head = other.tail = nullptr;
            other.length = 0;
        }
        

        ~DoublyLinkedList() 
        {
            clear();
        }
};


int main() 
{
    DoublyLinkedList<int> list1;
    DoublyLinkedList<int> list2;
    for (int i = 1; i <= 10; ++i) 
    {
        list1.push_back(i * 2);
        list2.push_back(i * 3);
    }
    std::cout << "Original List 1: ";
    for (Node<int>* current = list1.getHead(); current != nullptr; current = current->next) 
    {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;

    std::cout << "Original List 2: ";
    for (Node<int>* current = list2.getHead(); current != nullptr; current = current->next) 
    {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;


    list1.reverse();

    std::cout << "Reversed List 1: ";
    for (Node<int>* current = list1.getHead(); current != nullptr; current = current->next) 
    {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;


    list1.merge(list2);

    std::cout << "Merged List: ";
    for (Node<int>* current = list1.getHead(); current != nullptr; current = current->next) 
    {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;

    std::pair<bool, Node<int>*> cycleInfo = list1.detectCycleAndGetStartPoint(list1.getHead());
    if (cycleInfo.first) 
    {
        std::cout << "Cycle detected. Starting point: " << cycleInfo.second->data << std::endl;
    } 
    else 
    {
        std::cout << "No cycle detected." << std::endl;
    }

    list1.reverse();

    std::cout << "Reversed Merged List: ";
    for (Node<int>* current = list1.getHead(); current != nullptr; current = current->next) 
    {
        std::cout << current->data << " ";
    }
    std::cout << std::endl;

    list1.~DoublyLinkedList();
    list2.~DoublyLinkedList();
    return 0;
}
