#ifndef CGRAPH_DIRECTED_SPARSE_GRAPH_LIB_H
#define CGRAPH_DIRECTED_SPARSE_GRAPH_LIB_H
#include "graph.h"
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E>
    class directed_sparse_graph: public directed_graph<V, E> {
    public:
        using node_handle = size_t;
        using edge_handle = pair<node_handle, node_handle>;
        struct edge {
            node_handle to;
            E info;
        };
        directed_sparse_graph() {
            unique_handle = 0;
        }
        node_handle insert_node (V info) {
            //need expand or not?
            node_handle user_handle = generate_handle();
            size_t id = generate_id();
            //need expand or not?
            if (id >= node_vector.size()) {
                node_vector.push_back(info);
                node_flag.push_back(true);
                adj_list.push_back(vector<edge>());
            } else {
                node_vector[id] = info;
                node_flag[id] = true;
            }
            handle_to_id[user_handle] = id;
            return user_handle;
        }
        void erase_node (node_handle handle) {
            // TODO: check exception
            size_t id = handle_to_id[handle];
            if (node_flag[id] == false) return;
            // clear edge firstly
            // complexity: O(E)
            for (int i = 0; i < node_vector.size(); i++) {
                if (node_flag[i]) {
                    for (int j = 0; j < adj_list[i].size(); j++) {
                        if (adj_list[i][j].to == handle) {
                            adj_list[i].erase(adj_list[i].begin() + j);
                        }
                    }
                }
            }
            // clean node_vector
            node_flag[id] = false;
            //put this id to recycle stack
            recycle_handle.push(id);
            // remove mapping
            handle_to_id.erase(handle);
            // clean adj_matrix
            // IMPORTANT TODO:CLEAN THE EDGES
            
        }
        edge_handle insert_edge (node_handle handle1, node_handle handle2, E info) {
            // TODO: check exception
            // to: the user handle not the id in graph
            size_t v1 = handle_to_id[handle1];
            size_t v2 = handle_to_id[handle2];
            adj_list[v1].push_back(edge{handle2, info});
            return {handle1, handle2};
        }
        void erase_edge (edge_handle e) {
            size_t v1 = handle_to_id[e.first];
            size_t v2 = handle_to_id[e.second];
            if (!node_flag[v1]) return;
            int i = 0;
            for (i = 0; i < adj_list[v1].size(); i++) {
                //if (!node_flag[e.first]) continue;
                if (adj_list[v1][i].to == e.second)
                    break;
            }
            if (i == adj_list[v1].size()) return;
            adj_list[v1].erase(adj_list[v1].begin() + i);
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
        vector<vector<edge>> adj_list;
        vector<bool> node_flag;
        unordered_map<node_handle, size_t> handle_to_id;
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
    };
}
#endif