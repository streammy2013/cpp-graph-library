//
// Created by Mingjie Zhao on 4/20/18.
//

#ifndef CGRAPH_FIXED_DIRECTED_SPARSE_GRAPH_LIB_H
#define CGRAPH_FIXED_DIRECTED_SPARSE_GRAPH_LIB_H
#include "graph.h"
using namespace std;
namespace std_graph_lib {
    template<typename V, typename E>
    class fixed_directed_sparse_graph: public directed_graph<V, E> {
    public:
        struct edge { 
            node_handle to; 
            E info; 
        };
        fixed_directed_sparse_graph (int num) : node_num(num) {}
        node_handle insert_node (V info) {
            node_handle id = generate_id();
            if (id >= node_num) {
                cout << "The input node is out of bound." << endl;
                return -1;
            }
            node_vector.push_back(info);
            adj_list.push_back(vector<edge>());
            return id;
        }
        size_t node_cnt() {
            return node_vector.size();
        }
        edge_handle insert_edge (node_handle v1, node_handle v2, E info) {
            int cnt = node_vector.size();
            if (v1 >= cnt || v2 >= cnt) {
                cout << "The node has not been initialized. Please insert this node first." << endl;
                return {-1, -1};
            }
            if (v1 >= node_num || v2 >= node_num) {
                cout << "The input is out of bound." << endl;
                return {-1, -1};
            }
            //auto id = adj_list[v1].size();
            adj_list[v1].push_back(edge{v2, info});
            return {v1, v2};
        }
        void erase_edge (edge_handle e) {
            int cnt = node_vector.size();
            // TODO: check exception
            if (e.first >= cnt || e.second >= cnt) {
                cout << "The node has not been initialized. Please insert this node first." << endl;
                return;
            }
            int i = 0;
            for (i = 0; i < adj_list[e.first].size(); i++) {
                if (adj_list[e.first][i].to == e.second)
                    break;
            }
            if (i == adj_list[e.first].size()) return;
            adj_list[e.first].erase(adj_list[e.first].begin() + i);
        }
        void print_graph() {
            for (int i = 0; i < node_num; i++) {
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
        struct out_edges {
		    fixed_directed_sparse_graph& G;
		    size_t v1;
            struct iterator {
                fixed_directed_sparse_graph& G;
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
            int node_num;
            vector<vector<edge>> adj_list;
            vector<V> node_vector;
            node_handle generate_id() {
                return node_vector.size();
            }
    };
}
#endif //CGRAPH_FIXED_DIRECTED_SPARSE_GRAPH_LIB_H
