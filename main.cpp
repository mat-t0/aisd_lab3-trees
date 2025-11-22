#include <stdio.h>
#include "parsFile.hpp"
#include "avlTree.hpp"
#include <locale>


int main() {
    setlocale(LC_ALL, "rus");
    std::string input = readFile();


    if (!scobCheck(input) || !symCheck(input)) {
        std::cout << "Ошибка в формате строки" << std::endl;
        return 1;
    }


    TreeParser parser;
    binTree* root = parser.parse(input);

    if (root) {
        std::cout << "Дерево успешно построено" << "\n";
    }
    else {
        std::cout << "Ошибка структуры дерева" << std::endl;
    }


    for (int i = 0; i < inOrder(root).size(); i++) {
        std::cout << inOrder(root)[i] << " ";
    }
    std::cout << "\n" << "";


    avlTree tree;
    binTree* avlRoot = nullptr;

    for (int value : inOrder(root)) {
        avlRoot = tree.insert(value, avlRoot);
    }


    std::cout << "Поиск 5: " << (tree.search(avlRoot, 5) ? "найден" : "не найден") << std::endl;


    std::cout << "Pre-order: "; tree.printPreOrder(avlRoot); std::cout << std::endl;
    std::cout << "In-order: "; tree.printInOrder(avlRoot); std::cout << std::endl;
    std::cout << "Post-order: "; tree.printPostOrder(avlRoot); std::cout << std::endl;
    std::cout << "Level-order: "; tree.printLevelOrder(avlRoot); std::cout << std::endl;


    avlRoot = tree.deleteNode(avlRoot, 5);
    std::cout << "После удаления 5: "; tree.printInOrder(avlRoot); std::cout << std::endl;

    
    

    return 0;
}
