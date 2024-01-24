#include <iostream>
#include <vector>
#include <list>
#include <iterator>


template <typename K, typename V>
class HashNode 
{
    public:
        K key;
        V value;

        HashNode(const K& key, const V& value) : key(key), value(value) {}
};


template <typename K, typename V>
class HashTable 
{
    private:
        std::vector<std::list<HashNode<K, V>>> table;
        size_t capacity;

        size_t hashFunction(const K& key) const 
        {
            return std::hash<K>{}(key) % capacity;
        }

    public:
        HashTable(size_t capacity) : capacity(capacity) 
        {
            table.resize(capacity);
        }

        void insert(const K& key, const V& value) 
        {
            size_t index = hashFunction(key);
            HashNode<K, V> newNode(key, value);
            for (auto& node : table[index]) 
            {
                if (node.key == key) 
                {
                    node.value = value;
                    return;
                }
            }
            table[index].push_back(newNode);
        }
        bool remove(const K& key) 
        {
            size_t index = hashFunction(key);
            for (auto it = table[index].begin(); it != table[index].end(); ++it) 
            {
                if (it->key == key) 
                {
                    table[index].erase(it);
                    return true;
                }
            }
            return false;
        }

        bool get(const K& key, V& value) const 
        {
            size_t index = hashFunction(key);
            for (const auto& node : table[index]) 
            {
                if (node.key == key) 
                {
                    value = node.value;
                    return true;
                }
            }
            return false;
        }
};


int main() 
{

    HashTable<std::string, int> hashTable(10);

    hashTable.insert("one", 1);
    hashTable.insert("two", 2);
    hashTable.insert("three", 3);

    int value;

    if (hashTable.get("two", value)) 
    {
        std::cout << "Value for key 'two': " << value << std::endl;
    } 
    else 
    {
        std::cout << "Key 'two' not found." << std::endl;
    }

    hashTable.remove("three");

    if (hashTable.get("three", value)) 
    {
        std::cout << "Value for key 'three': " << value << std::endl;
    } 
    else 
    {
        std::cout << "Key 'three' not found." << std::endl;
    }

    return 0;
}
