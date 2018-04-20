//
// Created by Kaimao Yang on 2018/4/2.
//

#ifndef CGRAPH_GRAPH_H
#define CGRAPH_GRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <vector>
using namespace std;
template<typename U, typename T>
class Graph {
    using vertex_type = Vertex<U>;
    vector<vertex_type> node_vector;
    virtual int addNode()=0;
    virtual void addEdge()=0;
    virtual void eraseEdge()=0;
};

template<typename U, typename T>
class DirectedGraph: public Graph<T, U> {

};

template<typename T, typename U>
class FixedDirectedDenseGraph: public DirectedGraph<U, T> {	
    using vertex_type = Vertex<U>;
    using edge_type = Edge<T, U>;
    int node_num;
	vector<vector<T>> adj_matrix;
	vector<vertex_type> nodes;
	FixedDirectedDenseGraph (int num): node_num(num) {
		// initialization
    }
    void addNode (vertex_type info);   
    void addEdge (vertex_type v1, vertex_type v2, T info);
    void eraseEdge (vertex_type v1, vertex_type v2);
};

template<typename U, typename T>
class FixedDirectedSparseGraph: public DirectedGraph<U, T> {
    using vertex_type = Vertex<U>;
    using edge_type = Edge<T, U>;
	int node_num;
	vector<vector<edge_type>> adj_list;
	vector<vertex_type> nodes;
	FixedDirectedSparseGraph (int num) : node_num(num) {}
	void addNode (vertex_type info);
	void addEdge (vertex_type v1, vertex_type v2, T info);
	void eraseEdge (vertex_type v1, vertex_type v2);
};

template<typename U, typename T>
class DirectedDenseGraph: public DirectedGraph<U, T> {
    using vertex_type = Vertex<U>;
    using edge_type = Edge<T, U>;
	vector<vector<T>> adj_matrix;
	vector<vertex_type> nodes;
	vector<bool> flag;
	DirectedDenseGraph () {}
    int generate_id();
    void addNode (vertex_type v) {}
    void eraseNode(vertex_type v) {}
    void addEdge (vertex_type v1, vertex_type v2, T info);
    void eraseEdge (vertex_type v1, vertex_type v2);
};

template <class T, class U>
class DirectedSparseGraph: DirectedGraph<U, T> {
    using vertex_type = Vertex<U>;
    using edge_type = Edge<T, U>;
	vector<vector<edge_type>> adj_list;
	vector<vertex_type> nodes;
	vector<bool> flag;
	DirectedSparseGraph () {}
	int generate_id();
	void addNode (vertex_type v) {}
	void eraseNode(vertex_type v) {}
	void addEdge (vertex_type v1, vertex_type v2, T info);
	void eraseEdge (vertex_type v1, vertex_type v2);
};
#endif //CGRAPH_GRAPH_H
