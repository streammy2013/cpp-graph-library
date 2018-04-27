#ifndef USER_STRUCTS_H
#define USER_STRUCTS_H

#include "graph.h"
// node
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
    const size_t get_val() const{
        return miles;
    }
    dis operator+(dis d) const{
        return dis(miles + d.miles);
    }
};
#endif