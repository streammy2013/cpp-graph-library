//
// Created by Kaimao Yang on 2018/4/2.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H
#include <iostream>
#include <vector>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E>
    class graph {        
    public:     
        using node_handle = size_t;
        using edge_handle = pair<size_t, size_t>;   
        graph() {}
        virtual ~graph()=0;
        virtual node_handle insert_node(V)=0;
        virtual edge_handle insert_edge(node_handle, node_handle, E)=0;
        virtual void erase_edge(edge_handle)=0;
        virtual void print_graph()=0;
    private:
        vector<V> node_vector;
    };
    template<typename V, typename E>
    graph<V, E>::~graph(){

    }

    template<typename V, typename E>
    class directed_graph: public graph<V, E> {

    };
    
}

#endif //CGRAPH_GRAPH_H
