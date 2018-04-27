#ifndef CGRAPH_DIRECTED_DENSE_GRAPH_LIB_H
#define CGRAPH_DIRECTED_DENSE_GRAPH_LIB_H
#include "graph.h"
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E> 
    class directed_dense_graph: public directed_graph<V, E> {
    public:
        using node_handle = size_t;
        using edge_handle = pair<node_handle, node_handle>;
        using cost_type = E;
        struct edge {
            edge() {}
            edge(node_handle t, E i) {
                to = t;
                info = i;
            }
            node_handle get_to() {return to;}
            E get_info() {return info;}
        private:
            node_handle to;
            E info;
        };
        directed_dense_graph() {
            unique_handle = 0;
        }

        V handle_to_info (node_handle h) {
            size_t v = handle_to_id[h];
            return node_vector[v];
        }
        E end_to_edge (node_handle h1, node_handle h2) {
            size_t v1 = handle_to_id[h1];
            size_t v2 = handle_to_id[h2];
            return adj_matrix[v1][v2];
        }
        node_handle insert_node(V info) {
            node_handle user_handle = generate_handle();
            size_t id = generate_id();
            //need expand or not?
            if (id >= node_vector.size()) {
                node_vector.push_back(info);
                node_flag.push_back(true);
                id_to_handle.push_back(user_handle);
                expand_matrix();
            } else {
                node_vector[id] = info;
                node_flag[id] = true;
                id_to_handle[id] = user_handle;
            }
            handle_to_id[user_handle] = id;
            return user_handle;
        }

        void erase_node(node_handle handle) {
            // TODO: check exception
            size_t id = handle_to_id[handle];
            if (node_flag[id] == false) return;
            // clean node_vector
            node_flag[id] = false;
            //put this id to recycle stack
            recycle_handle.push(id);
            // remove mapping
            handle_to_id.erase(handle);
            // clean adj_matrix
            size_t dim = adj_matrix.size();
            for (int i = 0; i < dim; i++) {
                matrix_flag[id][i] = false;
                matrix_flag[i][id] = false;
            }
        }

        edge_handle insert_edge(node_handle handle1, node_handle handle2, E info) {
            //check exception
            size_t v1 = handle_to_id[handle1];
            size_t v2 = handle_to_id[handle2];
            adj_matrix[v1][v2] = info;
            matrix_flag[v1][v2] = true;
            return {handle1, handle2};
        }

        void erase_edge(edge_handle e) {
            size_t v1 = handle_to_id[e.first];
            size_t v2 = handle_to_id[e.second];
            matrix_flag[v1][v2] = false;
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
        struct nodes {
            directed_dense_graph& G;
            struct iterator {
                directed_dense_graph& G;
                node_handle v;
                bool operator!=(iterator it) {
                    return v != it.v;
                }
                iterator& operator++() {
                    v++;
                    while (v < G.node_vector.size() && !G.node_flag[v]) v++;
                    return {*this};
                }
                node_handle operator*() {
                    node_handle h = G.id_to_handle[v];
                    return h;
                }
            };
            iterator begin()const {
                size_t v = 0;
                while (v < G.node_vector.size() && !G.node_flag[v]) v++;
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
		    directed_dense_graph& G;
		    size_t v1;
            struct iterator {
                directed_dense_graph& G;
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
                    node_handle to = G.id_to_handle[v2];
                    return {to, G.adj_matrix[v1][v2]};
                }
            };
            iterator begin()const {
                size_t v2 = 0;
                while (v2 < G.adj_matrix[v1].size() && !G.matrix_flag[v1][v2]) v2++;
                return {G, v1, v2};
            }
            iterator end()const {
                return {G, v1, G.adj_matrix[v1].size()};
            }
        };
	//typedef out_edges::iterator edge_handle?
        out_edges out(node_handle handle) {
            size_t v = handle_to_id[handle];
            return {*this, v};
            // for (auto e: G.out(v)) {
            //		...
            //		any insert or erase operator is forbidden
            // }
        }
        const V& operator[](node_handle handle)const {
            size_t v = handle_to_id.at(handle);
            return node_vector[v];
        }
    private:
        vector<V> node_vector;
        vector<bool> node_flag;
        vector<vector<E>> adj_matrix;
        vector<vector<bool>> matrix_flag;
        unordered_map<node_handle, size_t> handle_to_id;
        vector<node_handle> id_to_handle;
        size_t unique_handle;
        stack<size_t> recycle_handle;
        node_handle generate_handle() {
            return unique_handle++;
        }
        size_t generate_id() {
            size_t id;
            if (node_vector.size() == 0) {
                id = 0;
            }
            else {
                if (recycle_handle.empty()) {
                    id = node_flag.size();
                    //node_flag.push_back(true);
                } else {
                    id = recycle_handle.top();
                    recycle_handle.pop();
                    //node_flag[id] = true;
                }
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