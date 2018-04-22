#include<vector>
using namespace std;
template<class U>
struct Node {
	int id;
	U info;
};

template<class T, class U>
struct Edge {
	Node<U> to;
	T info;
};
template<class U, class T>
class Graph {
    vector<Node<U>> node_vector;
    virtual int addNode()=0;
    virtual void addEdge()=0;
    virtual void eraseEdge()=0;
};

template<class U, class T>
class DirectedGraph: Graph<U, T> {
    
};

template<class T, class U> 
class FixedDirectedDenseGraph: DirectedGraph<U, T> {	
    int node_num;
	vector<vector<T>> adj_matrix;
	vector<Node<U>> nodes;
	FixedDirectedDenseGraph (int num): node_num(num) {
		// initialization
}
    int addNode (U info);   
    void addEdge (int v1, int v2, T info);
    void eraseEdge (int v1, int v2);
};

template<class T, class U>
class FixedDirectedSparseGraph: DirectedGraph<U, T> {
	int node_num;
	vector<vector<Edge<T>>> adj_list;
	vector<Node<U>> nodes;
	FixedDirectedSparseGraph (int num) : node_num(num) {}
	int addNode (U info);
	void addEdge (int v1, int v2, T info);
	void eraseEdge (int v1, int v2);
};

template<class T, class U>
class DirectedDenseGraph: DirectedGraph<U, T> {
	vector<vector<T>> adj_matrix;
	vector<Node<U>> nodes;
	vector<bool> flag;
	DirectedDenseGraph () {}
    int generate_id();
    int addNode (U info) {}
    void eraseNode(int id) {}
    void addEdge (int v1, int v2, T info);
    void eraseEdge (int v1, int v2);
};

template <class T, class U>
class DirectedSparseGraph: DirectedGraph<U, T> {
	vector<vector<Edge<T>>> adj_list;
	vector<Node<U>> nodes;
	vector<bool> flag;
	DirectedSparseGraph () {}
	int generate_id();
	int addNode (U info) {}
	void eraseNode(int id) {}
	void addEdge (int v1, int v2, T info);
	void eraseEdge (int v1, int v2);
};


// other function use template and concept
template<class T, class U>
bool is_cyclic (Graph<T, U> G) {}

template<class T, class U>
bool is_DAG (Graph<T, U> G) {
    // call is_cyclic
}

template<class T, class U>
vector<Node<U>> find_path_BFS(Graph<T, U> G, int v1, int v2) {}

template<class T, class U>
vector<Node<U>> find_path_DFS(Graph<T, U> G, int v1, int v2) {}

template<class T, class U, class L>
vector<L> singleSourceShortPath(Graph<T, U> G, int source) {
    // choose below three functions according to graph's type
} 

template<class T, class U, class L>
vector<L> bellmanFordPath (Graph<T, U> G, int source) {}

template<class T, class U, class L>
vector<L> dijkstraPath(Graph<T, U> G, int source) {}

template<class T, class U, class L>
vector<L> dagPath(Graph<T, U> G, int source) {}

// other auxiliary functions
