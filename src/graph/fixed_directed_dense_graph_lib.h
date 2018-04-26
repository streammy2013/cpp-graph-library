#ifndef CGRAPH_FIXED_DIRECTED_DENSE_GRAPH_LIB_H
#define CGRAPH_FIXED_DIRECTED_DENSE_GRAPH_LIB_H
#include "graph.h"
#include <vector>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E>
    class fixed_directed_dense_graph: public directed_graph<V, E> {	        
    public:        
        using node_handle = size_t;
        using edge_handle = pair<node_handle, node_handle>;
        using cost_type = E;
        fixed_directed_dense_graph () {}
        fixed_directed_dense_graph (size_t num) {
            node_num = num;
            for (int i = 0; i < node_num; i++) {
                adj_matrix.push_back(vector<E>(num, E()));
                matrix_flag.push_back(vector<bool>(node_num, false));
            }
        }

        struct edge {
            edge () {}
            edge (node_handle t, E i) {
                to = t;
                info = i;
            }
            node_handle get_to () {return to; }
            E get_info() {return info; }
        private:
            node_handle to;
            E& info;
        };

        size_t node_cnt() {
            return node_num;
        }
        V handle_to_info (node_handle v) {
            return node_vector[v];
        }
        E end_to_edge (node_handle h1, node_handle h2) {
            return adj_matrix[h1][h2];
        }
        node_handle insert_node (V info) {
            node_handle id = generate_id();
            if (id > node_num) {
                cout << "The input node is out of bound." << endl;
                return -1;
            }
            node_vector.push_back(info);
            return id;
        }  
        edge_handle insert_edge (node_handle v1, node_handle v2, E info) {
            if (v1 > node_num || v2 > node_num) {
                cout << "The input is out of bound." << endl;
                return {-1, -1};
            }
            adj_matrix[v1][v2] = info;
            matrix_flag[v1][v2] = true;
            return {v1, v2};
        }
        void erase_edge (edge_handle e) {
            matrix_flag[e.first][e.second] = false;
        }
        void print_graph() {
            for (int i = 0; i < node_num; i++) {
                cout << "Node " << i << ": ";
                cout << node_vector[i].to_string() << endl;
            }
            for (int i = 0; i < node_num; i++) {
                for (int j = 0; j < node_num; j++) {
                    if (matrix_flag[i][j]) {
                        cout << adj_matrix[i][j].to_string() << " ";
                    } else {
                        cout << 0 << " ";
                    }
                }
                cout << endl;
            }
        }
        struct nodes {
            fixed_directed_dense_graph& G;
            //nodes (fixed_directed_dense_graph g) { G = g;}
            struct iterator {
                fixed_directed_dense_graph& G;
                node_handle v;
                bool operator!=(iterator it) {
                    return v != it.v;
                }
                iterator& operator++() {
                    v++;
                    return *this;
                }
                node_handle operator*() {
                    return v;
                }
            };
            iterator begin()const {
                node_handle v = 0;
                return {G, v};
            }
            iterator end()const {
                return {G, G.node_vector.size()};
            }
        };
        nodes all_nodes() {
            return {*this};
        }
        struct out_edges {
		    fixed_directed_dense_graph& G;
		    size_t v1;
            struct iterator {
                fixed_directed_dense_graph& G;
                size_t v1;
                size_t v2;
                struct fake {
                    const size_t to;
                    const E& info;
                };
                bool operator!=(iterator it) {
                    return v2 != it.v2;
                }
                iterator& operator++() { 
                    v2++;
                    while (v2 < G.adj_matrix[v1].size() && !G.matrix_flag[v1][v2]) v2++;
                    return *this;
                }
                fake operator*() {
                    return {v2, G.adj_matrix[v1][v2]};
                }
            };
            iterator begin()const {
                size_t v2 = 0;
                while (v2 < G.adj_matrix[v1].size() && !G.matrix_flag[v1][v2]) v2++;
                return {G, v1, v2};
            }
            iterator end()const {
                return {G, v1, G.matrix_flag[v1].size()};
            }
        };
	//typedef out_edges::iterator edge_handle?
        out_edges out(node_handle v) {
            return {*this, v};
            // for (auto e: G.out(v)) {
            //		...
            //		any insert or erase operator is forbidden
            // }
        }
        const V& operator[](node_handle v)const {
            return node_vector[v];
        }

    private:
        size_t node_num;
        vector<vector<E>> adj_matrix;
        // indicator for valid edges
        vector<vector<bool>> matrix_flag;
        vector<V> node_vector;
        node_handle generate_id() {
            return node_vector.size();
        };
    };

}


#endif //CGRAPH_FIXED_DIRECTED_DENSE_GRAPH_LIB_H
