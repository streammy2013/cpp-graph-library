//
// Created by Kaimao Yang on 2018/4/2.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H
#include <vector>
#include <iostream>
#include <queue>

using namespace std;
namespace std_graph_lib {
    using node_handle = size_t;
    using edge_handle = pair<size_t, size_t>;
    template<typename V, typename E>
    class graph {        
    public:        
        graph() {}
        virtual ~graph()=0;
        virtual node_handle insert_node(V)=0;
        // TODO:不确定子类是否要实现所有的虚函数
        //virtual void erase_node(V)=0;
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
