#include <iostream>
#include <fstream>
#include "Hashtable.h"

int main() {
    Hashtable *hashtable;
    std::string command;
    while(std::cin >> command){
        if(command == "M"){
            int size;
            std::cin >> size;
            hashtable = new Hashtable(size);
            std::cout << "success" << std::endl;
        }
        else if(command == "INSERT"){
            std::string word;
            std::cin >> word;
            std::cout << hashtable->insert(word) << std::endl;
        }
        else if (command == "READ"){
            std::string filename;
            std::cin >> std::ws;
            std::cin >> filename;
            std::fstream fin(filename.c_str());
            if(!fin.is_open()){
                std::cout << "failure" << std::endl;
                continue;
            }
            std::cout << hashtable->tokenizeFile(fin) << std::endl;
        }
        else if( command == "TOKENIZE"){
            std::string word;
            std::cin >> word;
            std::cout << hashtable->tokenize(word) << std::endl;
        }
        else if(command == "RETRIEVE"){
            int t;
            std::cin >> t;
            std::cout << hashtable->retrieve(t) << std::endl;
        }
        else if(command == "STOK"){
            std::string currentWord = "";
            while(currentWord != "_DONE_"){
                std::cin >> currentWord;
                if(currentWord == "_DONE_"){
                    break;
                }
                std::cout << hashtable->tokenize(currentWord) << " ";
                currentWord = "";
            }
            std::cout << std::endl;
        }
        else if(command == "TOKS"){
            int t = 0;
            //std::cout << "TOKS" << std::endl;
            while(t != -1){
                std::cin >> t;
                if(t == -1){
                    break;
                }
                std::cout << hashtable->retrieve(t) << " ";
                t = 0;
            }
            std::cout << std::endl;
        }
        else if(command == "PRINT"){
            int k = 0;
            std::cin >> k;
            std::cout << hashtable->printTableIndex(k) << std::endl;
        }
        else if(command == "EXIT"){
            delete hashtable;
            break;
        }
    }
    return 0;
}
