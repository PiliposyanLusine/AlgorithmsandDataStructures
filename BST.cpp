#include <iostream>

class TreeNode 
{
    public:
        int data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int value) 
        {
            data = value;
            left = nullptr;
            right = nullptr;
        }
};

class BinarySearchTree 
{
    private:
        TreeNode* root;

        void inOrderTraversal(TreeNode* current) 
        {
            if (current == nullptr) 
            {
                return;
            }
            inOrderTraversal(current->left);
            std::cout << current->data << " ";
            inOrderTraversal(current->right);
        }

        void postOrderTraversal(TreeNode* current) 
        {
            if (current == nullptr) 
            {
                return;
            }
            postOrderTraversal(current->left);
            postOrderTraversal(current->right);
            std::cout << current->data << " ";
        }

        void preOrderTraversal(TreeNode* current) 
        {
            if (current == nullptr) 
            {
                return;
            }
            std::cout << current->data << " ";
            preOrderTraversal(current->left);
            preOrderTraversal(current->right);
        }


        void findSuccessor(TreeNode* node, int value, TreeNode*& succ) 
        {
        if (node == nullptr) 
        {
            return;
        }

        if (node->data == value) 
        {
            if (node->right) 
            {
                TreeNode* temp = node->right;
                while (temp->left) 
                {
                    temp = temp->left;
                }
                succ = temp;
            }
            return;
        }

        if (value < node->data) 
        {
            succ = node;
            findSuccessor(node->left, value, succ);
        } 
        else 
        {
            findSuccessor(node->right, value, succ);
        }
    }

        void findPredecessor(TreeNode* node, int value, TreeNode*& pred) 
        {
            if (node == nullptr) 
            {
                return;
            }

            if (node->data == value) 
            {
                if (node->left) 
                {
                    TreeNode* temp = node->left;
                    while (temp->right) 
                    {
                        temp = temp->right;
                    }
                    pred = temp;
                }
                return;
            }

            if (value < node->data) 
            {
                findPredecessor(node->left, value, pred);
            } 
            else 
            {
                pred = node;
                findPredecessor(node->right, value, pred);
            }
    }        



        int getHeightRecursive(TreeNode* node) 
        {
            if (node == nullptr) 
            {
                return 0;
            } 
            else 
            {
                int leftHeight = getHeightRecursive(node->left);
                int rightHeight = getHeightRecursive(node->right);
                return 1 + std::max(leftHeight, rightHeight);
            }
        }
        
        TreeNode* deleteRecursive(TreeNode* current, int value) 
        {
            if (current == nullptr) 
            {
                return current;
            }
            if (value < current->data) 
            {
                current->left = deleteRecursive(current->left, value);
            } 
            else if (value > current->data) 
            {
                current->right = deleteRecursive(current->right, value);
            } 
            else 
            {
            
                if (current->left == nullptr) 
                {
                    TreeNode* temp = current->right;
                    delete current;
                    return temp;
                } 
                else if (current->right == nullptr) 
                {
                    TreeNode* temp = current->left;
                    delete current;
                    return temp;
                } 
                TreeNode* temp = minValueNode(current->right);
                current->data = temp->data;
                current->right = deleteRecursive(current->right, temp->data);
            }
            return current;
        }

        TreeNode* minValueNode(TreeNode* node) 
        {
            TreeNode* current = node;
            while (current && current->left != nullptr) 
            {
                current = current->left;
            }
            return current;
        }
        
        TreeNode* insertRecursive(TreeNode* current, int value) 
        {
            if (current == nullptr) 
            {
                return new TreeNode(value);
            }

            if (value < current->data) 
            {
                current->left = insertRecursive(current->left, value);
            } 
            else if (value > current->data) 
            {
                current->right = insertRecursive(current->right, value);
            }

            return current;
        }
    
        
        bool searchRecursive(TreeNode* current, int value) 
        {
            
            if (current == nullptr) 
            {
                return false;
            }

            if (value == current->data) 
            {
                return true;
            } 
            else if (value < current->data) 
            {
                return searchRecursive(current->left, value);
            } 
            else 
            {
                return searchRecursive(current->right, value);
            }
        }

    public:
        BinarySearchTree() 
        {
            root = nullptr;
        }

        void insert(int value) 
        {
            root = insertRecursive(root, value);
        }
        
        bool search(int value) 
        {
            return searchRecursive(root, value);
        }
        void preOrderTraversal() 
        {
            preOrderTraversal(root);
            std::cout << std::endl;
        }

        void postOrderTraversal() 
        {
            postOrderTraversal(root);
            std::cout << std::endl;
        }


        void inOrderTraversal() 
        {
            inOrderTraversal(root);
            std::cout << std::endl;
        }
        void deleteNode(int value) 
        {
            root = deleteRecursive(root, value);
        }
        int getHeight() 
        {
            return getHeightRecursive(root);
        }
        int getPredecessor(int value) 
        {
            TreeNode* pred = nullptr;
            findPredecessor(root, value, pred);
            return pred ? pred->data : -1;  // Return -1 if no predecessor is found
        }
        int getSuccessor(int value) 
        {
            TreeNode* succ = nullptr;
            findSuccessor(root, value, succ);
            return succ ? succ->data : -1;  // Return -1 if no successor is found
        }

};

int main() 
{
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(8);
    std::cout << std::endl;
    std::cout << "In-Order Traversal of BST: ";
    bst.inOrderTraversal();

    std::cout << "Pre-Order Traversal of BST: ";
    bst.preOrderTraversal();

    std::cout << "Post-Order Traversal of BST: ";
    bst.postOrderTraversal();
    int searchValue = 5;
    if (bst.search(searchValue)) 
    {
        std::cout << searchValue << " found in the BST." << std::endl;
    } 
    else 
    {
        std::cout << searchValue << " not found in the BST." << std::endl;
    }

    searchValue = 12;
    if (bst.search(searchValue)) 
    {
        std::cout << searchValue << " found in the BST." << std::endl;
    } 
    else 
    {
        std::cout << searchValue << " not found in the BST." << std::endl;
    }

    std::cout << "Height of the BST: " << bst.getHeight() << std::endl;

    int predecessorValue = 8;
    std::cout << "Predecessor of " << predecessorValue << ": " << bst.getPredecessor(predecessorValue) << std::endl;

    int successorValue = 10;
    std::cout << "Successor of " << successorValue << ": " << bst.getSuccessor(successorValue) << std::endl;
    std::cout << std::endl;
    return 0;
}





