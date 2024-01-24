#include <iostream>
#include <vector>

class HashSet 
{
    private:
        static const int max_size = 10000;
        std::vector<std::vector<int>> buckets;
        int hash(int key)
        {
            return key % max_size;
        }
    

    public:
        HashSet() 
        {
            buckets.resize(max_size);
        }


        void insert(int key) 
        {
            int index = hash(key);
            for(int& num: buckets[index])
            {
                if(key == num)
                {
                    return;
                }
            }
            buckets[index].push_back(key);
        }


        void remove(int key) 
        {
            int index = hash(key);
            auto& bucket = buckets[index];
            for(auto it = bucket.begin(); it != bucket.end(); ++it)
            {
                if(*it == key)
                {
                    bucket.erase(it);
                    return;
                }
            }
        }


        bool contains(int key) 
        {
            int index = hash(key);
            for (int num : buckets[index]) 
            {
                if (num == key) 
                {
                    return true;
                }
            }
            return false;
        }
    };

    int main() 
    {
        HashSet mySet;
        mySet.insert(1);
        mySet.insert(2);
        mySet.insert(3);
        std::cout << "Contains 2: " << (mySet.contains(2) ? "true" : "false") << std::endl;
        std::cout << "Contains 4: " << (mySet.contains(4) ? "true" : "false") << std::endl;
        
        mySet.remove(2);
        std::cout << "Contains 2: " << (mySet.contains(2) ? "true" : "false") << std::endl;

        return 0;
    }
