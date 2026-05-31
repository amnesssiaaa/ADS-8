// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"
#include <string>
#include <algorithm>

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

void printFreq(BST<std::string>& tree) {
    int size = tree.size();
    BST<std::string>::NodeType** nodes = new BST<std::string>::NodeType*[size];
    int pos = 0;
    tree.collectNodes(nodes, pos);
    struct WordFreq {
        std::string word;
        int freq;
    };
    WordFreq* data = new WordFreq[size];
    for (int i = 0; i < size; i++) {
        data[i].word = nodes[i]->data;
        data[i].freq = nodes[i]->freq;
    }
    delete[] nodes;
    std::sort(data, data + size, [](const WordFreq& a, const WordFreq& b) {
            return a.freq > b.freq;
        });
    std::ofstream out("result/freq.txt");
    for (int i = 0; i < size; i++) {
        std::cout << data[i].word << " " << data[i].freq << std::endl;
        out << data[i].word << " " << data[i].freq << std::endl;
    }
    out.close();
    delete[] data;
}
