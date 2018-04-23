#ifndef CGRAPH_DIRECTED_SPARSE_GRAPH_LIB_H
#define CGRAPH_DIRECTED_SPARSE_GRAPH_LIB_H
#include "graph.h"
#include <vector>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E>
    class directed_sparse_graph: public directed_graph<V, E> {
    public:
        using node_handle = size_t;
        using edge_handle = pair<size_t, size_t>;
        struct edge {
            node_handle to;
            E info;
        };
        directed_sparse_graph() {}
        node_handle insert_node (V info) {
            node_handle id = generate_id();
            //need expand or not?
            if (id >= node_vector.size()) {
                node_vector.push_back(info);
                node_flag.push_back(true);
                adj_list.push_back(vector<edge>());
            } else {
                node_vector[id] = info;
                node_flag[id] = true;
            }
            return id;
        }
        void erase_node (node_handle v) {
            // TODO: check exception
            if (node_flag[v] == false) return;
            // clean node_vector
            node_flag[v] = false;
            // need to clean adj_matrix?
        }
        edge_handle insert_edge (node_handle v1, node_handle v2, E info) {
            // TODO: check exception
            adj_list[v1].push_back(edge{v2, info});
            return {v1, v2};
        }
        void erase_edge (edge_handle e) {
            if (!node_flag[e.first]) return;
            int i = 0;
            for (i = 0; i < adj_list[e.first].size(); i++) {
                if (!node_flag[e.first]) continue;
                if (adj_list[e.first][i].to == e.second)
                    break;
            }
            if (i == adj_list[e.first].size()) return;
            adj_list[e.first].erase(adj_list[e.first].begin() + i);
        }

        void print_graph() {
            size_t node_num = node_flag.size();
            for (int i = 0; i < node_num; i++) {
                if (node_flag[i]) {
                    cout << "Node " << i << ": ";
                    cout << node_vector[i].to_string() << endl;
                    cout << "Edges:" << endl;
                    for (const auto& e : (*this).out(i)) {
                        auto to = e.to;
                        auto info = e.value;
                        cout << to << ", " << info.to_string() << endl;
                    }
                }                
            }
        }
        struct out_edges {
		    directed_sparse_graph& G;
		    size_t v1;
            struct iterator {
                directed_sparse_graph& G;
                size_t v1;
                size_t idx;
                size_t v2;
                struct fake {
                    const size_t to;
                    const E& value;
                };
                bool operator!=(iterator it) {
                    return idx != it.idx;
                }
                iterator& operator++() { 
                    idx++;
                    while (idx < G.adj_list[v1].size()) idx++;
                    return *this;
                }
                fake operator*() {
                    return {G.adj_list[v1][idx].to, G.adj_list[v1][idx].info};
                }
            };
            iterator begin()const {
                if (G.adj_list[v1].size() == 0) return end();
                else return {G, v1, 0, G.adj_list[v1][0].to};
            }
            iterator end()const {
                return {G, v1, G.adj_list[v1].size(), G.adj_list[v1].size()};
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
        vector<vector<edge>> adj_list;
        vector<bool> node_flag;
        node_handle generate_id() {
            if (node_vector.size() == 0) return 0;
            node_handle id = 0;
            for (id = 0; id < node_flag.size(); id++) {
                if (node_flag[id] == false) break;
            }
            return id;
        }
    };
}
#endif