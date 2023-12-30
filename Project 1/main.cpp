#include <iostream>
#include <string>
#include "children.h"
#include "child.h"

int main() {
    Children children{};
    std::string command;
    double arg1 = 0;
    double arg2 = 0;
    //written by chatgpt
    while (std::cin >> command) {
        if (command == "SPAWN") {
            std::cin >> arg1 >> arg2;
            std::cout << (children.spawn(arg1, arg2) ? "success" : "failure") << std::endl;
        } else if (command == "PRT") {
            std::cin >> arg1;
            std::cout << children.prt(arg1) << std::endl;
        } else if (command == "TIME") {
            std::cin >> arg1;
            std::cout << children.time(arg1) << std::endl;
        } else if (command == "NUM") {
            std::cout << children.numChildren() << std::endl;
        } else if (command == "OVER") {
            std::cout << children.over() << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}





