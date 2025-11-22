#include <iostream>
#include <string>
#include <vector>

struct binTree {
    int data;
    int height = 0;
    binTree* left = nullptr;
    binTree* right = nullptr;
};

class TreeParser {
private:

    void skipSpaces(const std::string& str, int& index) {
        while (index < str.length() && str[index] == ' ') {
            index++;
        }
    }


    int readNumber(const std::string& str, int& index) {
        int num = 0;
        while (index < str.length() && isdigit(str[index])) {
            num = num * 10 + (str[index] - '0');
            index++;
        }
        return num;
    }

public:

    binTree* parse(const std::string& str) {
        int index = 0;
        return parseSubtree(str, index);
    }

private:

    binTree* parseSubtree(const std::string& str, int& index) {
        skipSpaces(str, index);

        // 1. Должна быть открывающая скобка
        if (str[index] != '(') return nullptr;
        index++; 

        skipSpaces(str, index);

        // 2. Читаем число 
        int value = readNumber(str, index);
        binTree* node = new binTree;
        node->data = value;
        node->left = nullptr;
        node->right = nullptr;

        skipSpaces(str, index);

        // 3. Читаем детей 
        int childCount = 0;
        while (str[index] == '(') {
            if (childCount == 0) {
                node->left = parseSubtree(str, index);
                childCount++;
            }
            else if (childCount == 1) {
                node->right = parseSubtree(str, index);
                childCount++;
            }
            else {
                delete node;
                return nullptr;
            }
            skipSpaces(str, index);
        }

        // 4. Должна быть закрывающая скобка
        if (str[index] != ')') {
            delete node;
            return nullptr;
        }
        index++; 

        return node;
    }
};

inline void inOrderHelper(binTree* root, std::vector<int>& result) {
    if (root == nullptr) return;

    inOrderHelper(root->left, result);    
    result.push_back(root->data);         
    inOrderHelper(root->right, result);   
}

inline std::vector<int> inOrder(binTree* root) {
    std::vector<int> result;
    inOrderHelper(root, result);
    return result;
}
