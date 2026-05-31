// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "ошибка" << std::endl;
        return;
    }
    std::string word;
    while (!file.eof()) {
        int ch = file.get();
        if ((ch >= 'A' && ch <= 'Z') ||
            (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch += ('a' - 'A');
            }
            word += static_cast<char>(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}
