//
// Created by kijij on 10/2/2023.
//

#include "Hashtable.h"
#include <fstream>

//function copied from chatGPT
int sumAsciiValues(const std::string& str) {
    int sum = 0;
    for (char c : str) {
        if (std::isalpha(c)) {
            sum += static_cast<int>(c);
        } else {
            return -1; // Return -1 if non-alphabetic character is found
        }
    }
    return sum;
}

std::string Hashtable::printTableIndex(int i) {
    Node* indexedElement = table[i];
    if (indexedElement == nullptr){
        return "chain is empty";
    }
    std::string returnValue = "";
    while(indexedElement != nullptr){
        returnValue = returnValue + std::to_string(indexedElement->getAscii()) + " ";
        indexedElement = indexedElement->get_next();
    }
    return returnValue;
}

int Hashtable::hash(int key){ //hash function
    return key % m;
}

std::string Hashtable::tokenizeFile(std::fstream &fin) {
    std::string toRead;
    //more variables?
    int dictionarySizeBefore = dictionarySize;
    while(fin >> toRead){
        //toRead contains the next word
        insert(toRead);
    }
    if(dictionarySizeBefore == dictionarySize){
        return "failure";
    }
    return "success";
}

//partially copied from chatGPT
void Hashtable::addToDynamicArray(const std::string& str) {
    if (dictionarySize >= maxDictionarySize) {
        // The dynamic array is full; allocate a larger one.
        int newDynamicArraySize = dictionarySize + 10; // Increase the size as needed
        std::string* newStringArray = new std::string[newDynamicArraySize];

        // Copy existing elements to the new array
        for (int i = 0; i < dictionarySize; ++i) {
            newStringArray[i] = dictionary[i];
        }

        // Add the new element
        newStringArray[dictionarySize] = str;
        for(int i = dictionarySize + 1; i < newDynamicArraySize; i++){
            newStringArray[i] = "UNKNOWN";
        }
        // Deallocate memory for the old array
        delete[] dictionary;

        // Update to the new array and size
        dictionary = newStringArray;
        dictionarySize++;
        maxDictionarySize = newDynamicArraySize;
    } else {
        // There is space in the current dynamic array, so add the element.
        dictionary[dictionarySize] = str;
        dictionarySize++;
    }
}

Hashtable::Hashtable(int size) { //should be synonymous with the command m
    m = size; //initialize m
    maxDictionarySize = size * 2;
    dictionarySize = 0;
    table = new Node*[m];
    dictionary = new std::string[maxDictionarySize];
    for(int i = 0; i < m; i++){
        table[i] = nullptr; //initialize hashtable to all be nullptr
    }
    for(int i = 0; i < maxDictionarySize; i++){
        dictionary[i] = "UNKNOWN";
    }
}

Hashtable::~Hashtable(){
    for(int i = 0; i < m; i++){ //iterate through hashtable entries
        Node* p_current = table[i];
        while(p_current != nullptr){ //delete all the Nodes in that specific entry
            Node* old = p_current;
            p_current = p_current->get_next();
            delete old;
            old = nullptr;
        }
    }
    delete[] table;
    delete[] dictionary; //delete dictionary
}

std::string Hashtable::insert(std::string word){
    int asciiValue = sumAsciiValues(word);
    if(asciiValue == -1){ //non alphabetic value in word
        return "failure";
    }
    int hashValue = hash(asciiValue);
    Node *newNode = new Node(nullptr, word, asciiValue, dictionarySize);
    if(table[hashValue] == nullptr){ //first node in that hash spot
        table[hashValue] = newNode;
        addToDynamicArray(word);
        return "success";
    }
    else{ //gotta loop through the linked list there
        Node *current = table[hashValue];
        while(current != nullptr){
            if(current->getWord() == word){
                delete newNode;
                return "failure"; //word already exists
            }
            current = current->get_next(); //get next pointer
        }
        //I can only insert at the beginning now cause I didn't keep track of my previous pointer
        newNode->set_next(table[hashValue]);
        table[hashValue] = newNode;
        addToDynamicArray(word);
        return "success";
    }
}

std::string Hashtable::tokenize(std::string word){
    int hashValue = hash(sumAsciiValues(word));
    if(sumAsciiValues(word) == -1){
        return "0";
    }
    if(table[hashValue] == nullptr){ //nothing there
        return "0";
    }
    else{
        Node *current = table[hashValue];
        while(current != nullptr){
            if(current->getWord() == word){
                return std::to_string(current->getToken() + 1);
                //return token value, but need to add one since token is actually index of dictionary
            }
            current = current -> get_next();
        }
        return "0"; //looped through hashtable entry and still couldn't find word
    }
}

std::string Hashtable::retrieve(int t){
    return t >= 1 && t < maxDictionarySize ? dictionary[t - 1] : "UNKNOWN"; //gives the index i think
}


