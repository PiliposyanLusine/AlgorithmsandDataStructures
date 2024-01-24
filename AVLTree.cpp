#include <iostream>


struct Node
{
    int key;
    Node* left;
    Node* right;
    int height;
};


int height(Node* node)
{
    if(!node)
    {
        return 0;
    }
    return node->height;
}

void updateHeight(Node* node)
{
    node->height =  1 + std::max(height(node->left), height(node->right));
}


Node* rotateRight(Node* y)
{
    Node* x = y->left;
    Node* T2 = x->right;
    y->right = x;
    x->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}


Node* rotateLeft(Node* y)
{
    Node* x = y->right;
    Node* T2 = x->left;
    y->right = T2;
    x->left = y;
    updateHeight(y);
    updateHeight(x);

    return x;    
}




Node* balance(Node* node)
{
    int balanceFactor = height(node->left) - height(node->right);

    if (balanceFactor > 1)
    {
        if (height(node->left->left) >= height(node->left->right))
        {
            return rotateRight(node);
        }
        else
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    if (balanceFactor < -1)
    {
        if (height(node->right->right) >= height(node->right->left))
        {
            return rotateLeft(node);
        }
        else
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}




void inOrder(Node* node)
{
    if(!node)
    {
        return;
    }
    inOrder(node->left);
    std::cout << node->key << std::endl;
    inOrder(node->right);
}

Node* insert(Node* node, int key)
{
    if(!node)
    {   
        return new Node{key, nullptr, nullptr, 1};
    }
    if(key < node->key)
    {
        node->left = insert(node->left, key);
    }
    if(key > node->key)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        return node;
    }
    updateHeight(node);
    return balance(node);
}



int main()
{
    Node* root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    std::cout << "In-order traversal of AVL tree: ";
    inOrder(root);
}