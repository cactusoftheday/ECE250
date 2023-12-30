//
// Created by kijij on 11/4/2023.
//

#include "illegal_exception.h"
illegal_exception::illegal_exception() : std::runtime_error("illegal argument") {}