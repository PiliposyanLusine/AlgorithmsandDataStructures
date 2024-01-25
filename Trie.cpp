#include <iostream>
#include <string>

class Trie
{
private:
    struct TrieNode
    {

        TrieNode* children[26];
        bool isEnd;
        TrieNode() 
        {
            for (int i = 0; i < 26; ++i)
            {
                children[i] = nullptr;
            }
            isEnd = false;
        }
    };
    TrieNode* root;

    TrieNode* remove(TrieNode* root, const std::string& str, int deep = 0)
    {
        if (!root)
        {
            return root;
        }
        if (deep == str.length())
        {
            root->isEnd = false;
            if (isEmpty(root))
            {
                delete root;
                root = nullptr;
            }
            return root;
        }
        int index = str[deep] - 'a';
        root->children[index] = remove(root->children[index], str, deep + 1);
        if (isEmpty(root) && !root->isEnd)
        {
            delete root;
            root = nullptr;
        }
        return root; 
    }

public:
    Trie() 
    {
        root = new TrieNode();
    }


    ~Trie()
    {
        deleteTrie(root);
    }

    void deleteTrie(TrieNode* node)
    {
        if (node == nullptr)
            return;
        for (int i = 0; i < 26; ++i)
        {
            deleteTrie(node->children[i]);
        }
        delete node;
    }


    void insert(const std::string& str)
    {
        TrieNode* tmp = root;
        for (int i = 0; i < str.length(); ++i)
        {
            int index = str[i] - 'a';
            if (!tmp->children[index])
            {
                tmp->children[index] = new TrieNode();
            }
            tmp = tmp->children[index];
        }
        tmp->isEnd = true;
    }

    bool Search(const std::string& str)
    {
        TrieNode* tmp = root;
        for (int i = 0; i < str.length(); ++i)
        {
            int index = str[i] - 'a';
            if (!tmp->children[index])
            {
                return false;
            }
            tmp = tmp->children[index];
        }
        return tmp->isEnd;
    }

    bool isEmpty(TrieNode* k)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (k->children[i])
            {
                return false;
            }
        }
        return true;
    }

    void Erase(const std::string& str)
    {
        root = remove(root, str); 
    }
};


int main()
{
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("bat");
    trie.insert("car");

    std::cout << "Searching for 'apple': " << (trie.Search("apple") ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 'app': " << (trie.Search("app") ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 'banana': " << (trie.Search("banana") ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 'bat': " << (trie.Search("bat") ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 'car': " << (trie.Search("car") ? "Found" : "Not Found") << std::endl;
    std::cout << "Searching for 'dog': " << (trie.Search("dog") ? "Found" : "Not Found") << std::endl;

    trie.Erase("apple");
    std::cout << "After erasing 'apple', searching for 'apple': " << (trie.Search("apple") ? "Found" : "Not Found") << std::endl;

    return 0;
}
