#include "binTree.hpp"
#include <queue>

class avlTree {
public:
    binTree* insert(int data, binTree* root) {
        if (root == nullptr) {
            binTree* newNode = new binTree;
            newNode->data = data;
            return newNode;
        }

        if (data > root->data) {
            root->right = insert(data, root->right);
        }
        else if (data < root->data) {
            root->left = insert(data, root->left);
        }

        updateHeight(root);

        
        int balance = getBalance(root);

        // Left 
        if (balance > 1 && data < root->left->data) {
            return rotateRight(root);
        }

        // Right
        if (balance < -1 && data > root->right->data) {
            return rotateLeft(root);
        }

        // Left Right
        if (balance > 1 && data > root->left->data) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Left 
        if (balance < -1 && data < root->right->data) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }


    binTree* deleteNode(binTree* root, int data) {
        if (root == nullptr) return root;


        if (data < root->data) {
            root->left = deleteNode(root->left, data);
        }
        else if (data > root->data) {
            root->right = deleteNode(root->right, data);
        }
        else {
            //удаляем
            if (root->left == nullptr) {
                binTree* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                binTree* temp = root->left;
                delete root;
                return temp;
            }
            else {
                //минимум в правом поддереве
                binTree* temp = root->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

    
        updateHeight(root);
        int balance = getBalance(root);


        // Left
        if (balance > 1 && getBalance(root->left) >= 0) {
            return rotateRight(root);
        }
        // Left Right
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        // Right 
        if (balance < -1 && getBalance(root->right) <= 0) {
            return rotateLeft(root);
        }
        // Right Left
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }



    bool search(binTree* root, int data) {
        if (root == nullptr) return false;
        if (root->data == data) return true;
        if (data < root->data) return search(root->left, data);
        return search(root->right, data);
    }



    void printPreOrder(binTree* root) {
        if (root == nullptr) return;
        std::cout << root->data << " ";
        printPreOrder(root->left);
        printPreOrder(root->right);
    }

    void printInOrder(binTree* root) {
        if (root == nullptr) return;
        printInOrder(root->left);
        std::cout << root->data << " ";
        printInOrder(root->right);
    }

    void printPostOrder(binTree* root) {
        if (root == nullptr) return;
        printPostOrder(root->left);
        printPostOrder(root->right);
        std::cout << root->data << " ";
    }

    void printLevelOrder(binTree* root) {
        if (root == nullptr) return;

        std::queue<binTree*> q;
        q.push(root);

        while (!q.empty()) {
            binTree* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
    }



private:
    void updateHeight(binTree* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        
    }
    int getHeight(binTree* node) {
        return node == nullptr ? -1 : node->height;
    }
    
    int getBalance(binTree* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Правый поворот 
    binTree* rotateRight(binTree* y) {
        binTree* x = y->left;
        binTree* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;  
    }

    // Левый поворот   
    binTree* rotateLeft(binTree* x) {
        binTree* y = x->right;
        binTree* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y; 
    }


};
