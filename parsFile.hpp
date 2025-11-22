#include <iostream>
#include <fstream>
#include <string>

std::string readFile() {
    std::ifstream file("scobki.txt"); 
    std::string line;
    std::string fileScob;


    if (file.is_open()) {

        while (std::getline(file, line)) {
            fileScob += line;
        }
        file.close(); 
    }
    else {
        std::cerr << "Не удалось открыть файл" << std::endl;
    }
    return fileScob;
}

int scobCheck(std::string line) {
    int countOpen = 0;
    int countClose = 0;

    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '(') {
            countOpen++;
        }
        else if (line[i] == ')') {
            countOpen--;
            if (countOpen < 0) {
                return 0;  
            }
        }
    }
    if (countOpen != 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int symCheck(std::string line) {
    for (int i = 0; i < line.length(); i++) {
        char c = line[i];
        if (!(std::isdigit(c) || c == ' ' || c == '(' || c == ')')) {
            return 0; 
        }
    }
    return 1;
}
