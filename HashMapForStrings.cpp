#include <iostream>
#include <vector>
#include <list>

class HashMap 
{
    private:
        static const int TABLE_SIZE = 100; 
        std::vector<std::list<std::pair<std::string, std::string>>> table;

        int hash(const std::string& key) 
        {
            int hash = 0;
            for (char c : key) 
            {
                hash = (hash * 31 + c) % TABLE_SIZE;
            }
            return hash;
        }

    public:
        HashMap() 
        {
            table.resize(TABLE_SIZE);
        }


        void insert(const std::string& key, const std::string& value) 
        {
            int index = hash(key);
            for (auto& kvp : table[index]) 
            {
                if (kvp.first == key) {
                    kvp.second = value; 
                    return;
                }
            }
            table[index].push_back(std::make_pair(key, value)); 
        }

        
        std::string get(const std::string& key) 
        {
            int index = hash(key);
            for (const auto& kvp : table[index]) 
            {
                if (kvp.first == key) 
                {
                    return kvp.second; 
                }
            }
            return ""; 
        }


        void remove(const std::string& key) 
        {
            int index = hash(key);
            table[index].remove_if([&key](const auto& kvp) {return kvp.first == key; });
        }
    };

    int main() 
    {
        HashMap hashMap;

        hashMap.insert("key1", "value1");
        hashMap.insert("key2", "value2");
        hashMap.insert("key3", "value3");

        std::cout << "Value for key2: " << hashMap.get("key2") << std::endl;

        hashMap.remove("key1");

        std::cout << "Value for key1 after removal: " << hashMap.get("key1") << std::endl;

        return 0;
    }
