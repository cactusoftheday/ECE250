//
// Created by kijij on 11/4/2023.
//

#ifndef PROJECT3_ILLEGAL_EXCEPTION_H
#define PROJECT3_ILLEGAL_EXCEPTION_H

#include <string>
#include <stdexcept>

class illegal_exception : public std::runtime_error {
public:
    illegal_exception();
};


#endif //PROJECT3_ILLEGAL_EXCEPTION_H
