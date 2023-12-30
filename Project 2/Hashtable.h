//
// Created by kijij on 10/2/2023.
//

#ifndef PROJECT_2_HASHTABLE_H
#define PROJECT_2_HASHTABLE_H


#include <string>
#include "Node.h"

class Hashtable {
public:
    Hashtable(int m);
    ~Hashtable();
    std::string insert(std::string word);
    std::string tokenize(std::string word);
    std::string retrieve(int t);
    std::string printTableIndex(int i);
    std::string tokenizeFile(std::fstream& fin);
private:
    int m; //hash table size
    int dictionarySize; //current dictionary size
    int maxDictionarySize; //max dictionary size
    Node** table;
    std::string* dictionary;
    int hash(int key);
    void addToDynamicArray(const std::string &str);
};


#endif //PROJECT_2_HASHTABLE_H
