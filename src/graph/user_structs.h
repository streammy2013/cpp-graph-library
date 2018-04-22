#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H

#include "graph.h"
struct city {
    string name;
    city(string input): name(input) {} 
    string to_string() {
        return name;
    }
};

struct dis {
    size_t miles;
    dis(){}
    dis(size_t input): miles(input) {}
    string to_string() {
        return std::to_string(miles);
    }
};
#endif