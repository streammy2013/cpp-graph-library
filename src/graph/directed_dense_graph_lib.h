#ifndef CGRAPH_DIRECTED_DENSE_GRAPH_LIB_H
#define CGRAPH_DIRECTED_DENSE_GRAPH_LIB_H
#include "graph.h"
#include <vector>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E> 
    class directed_dense_graph: public directed_graph<V, E> {
    public:
        using node_handle = size_t;
        using edge_handle = pair<size_t, size_t>;
        struct edge {
            node_handle to;
            E info;
        };
        directed_dense_graph() {}
        node_handle insert_node(V info) {
            node_handle id = generate_id();
            //need expand or not?
            if (id >= node_vector.size()) {
                node_vector.push_back(info);
                node_flag.push_back(true);
                expand_matrix();
            } else {
                node_vector[id] = info;
                node_flag[id] = true;
            }
            return id;
        }

        void erase_node(node_handle v) {
            // TODO: check exception
            if (node_flag[v] == false) return;
            // clean node_vector
            node_flag[v] = false;
            // clean adj_matrix
            size_t dim = adj_matrix.size();
            for (int i = 0; i < dim; i++) {
                matrix_flag[v][i] = false;
                matrix_flag[i][v] = false;
            }
        }

        edge_handle insert_edge(node_handle v1, node_handle v2, E info) {
            //check exception
            
            adj_matrix[v1][v2] = info;
            matrix_flag[v1][v2] = true;
            return {v1, v2};
        }

        void erase_edge(edge_handle e) {
            matrix_flag[e.first][e.second] = false;
        }

        void print_graph() {
            size_t node_num = node_vector.size();
            for (int i = 0; i < node_vector.size(); i++) {
                if (node_flag[i]) {
                    cout << "Node " << i << ": ";
                    cout << node_vector[i].to_string() << endl;
                }
                
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
        struct out_edges {
		    directed_dense_graph& G;
		    size_t v1;
            struct iterator {
                directed_dense_graph& G;
                size_t v1;
                size_t v2;
                struct fake {
                    const size_t to;
                    const E& value;
                };
                bool operator!=(iterator it) {
                    return v2 != it.v2;
                }
                iterator& operator++() { 
                    v2++;
                    while (v2 < G.adj_matrix[v1].size() && G.matrix_flag[v1][v2]) v2++;
                    return *this;
                }
                fake operator*() {
                    return {v2, G.adj_matrix[v1][v2]};
                }
            };
            iterator begin()const {
                size_t v2 = 0;
                while (v2 < G.adj_matrix[v1].size() && G.matrix_flag[v1][v2]) v2++;
                return {G, v1, v2};
            }
            iterator end()const {
                return {G, v1, G.adj_matrix[v1].size()};
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
        vector<V> node_vector;
        vector<bool> node_flag;
        vector<vector<E>> adj_matrix;
        vector<vector<bool>> matrix_flag;
        node_handle generate_id() {
            if (node_vector.size() == 0) return 0;
            node_handle id = 0;
            for (id = 0; id < node_flag.size(); id++) {
                if (node_flag[id] == false) break;
            }
            return id;
        }
        void expand_matrix() {
            size_t dim = adj_matrix.size();
            adj_matrix.push_back(vector<E>(dim + 1, E()));
            matrix_flag.push_back(vector<bool>(dim + 1, false));
            for (int i = 0; i < dim; i++) {
                adj_matrix[i].push_back(E());
                matrix_flag[i].push_back(false);
            }
        }
    };
}
#endif