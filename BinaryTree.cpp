#include <iostream>

struct TreeNode 
{
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree 
{
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* root, int val) 
    {
        if (root == nullptr) 
        {
            return new TreeNode(val);
        }

        if (val < root->data) 
        {
            root->left = insert(root->left, val);
        } 
        else if (val > root->data) 
        {
            root->right = insert(root->right, val);
        }

        return root;
    }

    TreeNode* search(TreeNode* root, int val) 
    {
        if (root == nullptr || root->data == val) 
        {
            return root;
        }

        if (val < root->data) 
        {
            return search(root->left, val);
        } 
        else 
        {
            return search(root->right, val);
        }
    }

    TreeNode* deleteNode(TreeNode* root, int val) 
    {
    if (!root ) 
    {
        return root;
    }

    if (val < root->data) 
    {
        root->left = deleteNode(root->left, val);
    } 
    else if (val > root->data) 
    {
        root->right = deleteNode(root->right, val);
    } 
    else 
    {

        if (!root->left && !root->right) 
        {
            delete root;
            return nullptr;
        }

        if (root->left == nullptr) 
        {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) 
        {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}


    TreeNode* findMin(TreeNode* node) 
    {
        while (node->left ) 
        {
            node = node->left;
        }
        return node;
    }

    void inorderTraversal(TreeNode* root) 
    {
        if (root )
        {
            inorderTraversal(root->left);
            std::cout << root->data << " ";
            inorderTraversal(root->right);
        }
    }

    int height(TreeNode* root) 
    {
        if (!root ) 
        {
            return 0;
        } 
        else 
        {
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);
            return 1 + std::max(leftHeight, rightHeight);
        }
    }

    int countNodes(TreeNode* root) 
    {
        if (root == nullptr) 
        {
            return 0;
        } 
        else 
        {
            return 1 + countNodes(root->left) + countNodes(root->right);
        }
    }

    int countLeaves(TreeNode* root)
    {
        if (root == nullptr) 
        {
            return 0;
        } 
        else if (!root->left  && !root->right ) 
        {
            return 1;
        } 
        else 
        {
            return countLeaves(root->left) + countLeaves(root->right);
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int val) 
    {
        root = insert(root, val);
    }

    TreeNode* search(int val) 
    {
        return search(root, val);
    }

    void deleteNode(int val) 
    {
        root = deleteNode(root, val);
    }

    void inorderTraversal() 
    {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    int height() 
    {
        return height(root);
    }

    int countNodes() 
    {
        return countNodes(root);
    }

    int countLeaves() 
    {
        return countLeaves(root);
    }
};

int main() {
    BinaryTree tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);


    std::cout << "In-order traversal: ";
    tree.inorderTraversal();


    int searchValue = 4;
    TreeNode* searchResult = tree.search(searchValue);
    if (searchResult ) 
    {
        std::cout << "Node with value " << searchValue << " found in the tree." << std::endl;
    } 
    else 
    {
        std::cout << "Node with value " << searchValue << " not found in the tree." << std::endl;
    }
    int deleteValue = 7;
    tree.deleteNode(deleteValue);
    std::cout << "After deleting node with value " << deleteValue << ": ";
    tree.inorderTraversal();


    std::cout << "Height of the tree: " << tree.height() << std::endl;

    std::cout << "Total number of nodes: " << tree.countNodes() << std::endl;
    std::cout << "Number of leaf nodes: " << tree.countLeaves() << std::endl;

    return 0;
}
