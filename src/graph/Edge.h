//
// Created by Kaimao Yang on 2018/4/2.
//

#ifndef CGRAPH_EDGE_H
#define CGRAPH_EDGE_H
#include "Vertex.h"
template<typename T, typename U>
struct Edge {
    using vertex_type = Vertex<U>;
    vertex_type to;
    T info;
};
#endif //CGRAPH_EDGE_H
