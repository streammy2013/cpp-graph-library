#ifndef PATH_STRUCTS_H
#define PATH_STRUCTS_H
#include <vector>
#include <memory>
#include "graph_concepts.h"
#include "graph.h"
using namespace std;
using namespace std_graph_lib;
template<typename G>
struct node_state;
template<typename G>
struct node_state: public std::enable_shared_from_this<node_state<G>> {
    using node_handle = typename G::node_handle;
    using Cost = typename G::cost_type;
    node_handle handle;
    shared_ptr<node_state<G>> parent;
    G graph;
    Cost cost;
    node_state(node_handle v, shared_ptr<node_state<G>> p, G g, Cost c) {
        handle = v;
        parent = p;
        graph = g;
        cost = c;
    }
    bool operator==(const node_state& cns) const {
        // different graph may have same handle;
        return handle == cns.handle && graph == cns.handle;
    }
    bool operator!=(const node_state& cns) const {
        // different graph may have same handle;
        return handle != cns.handle;
    }
    bool operator==(nullptr_t n) const {
        if (this == nullptr) {
            return true;
        } else return false;
    }
    bool operator!=(nullptr_t n) const {
        if (this != nullptr) {
            return true;
        } else return false;
    }
    vector<shared_ptr<node_state<G>>> out_states() {
        vector<shared_ptr<node_state<G>>> out;
        for (const auto& e: graph.out(handle)) {
            // TODO
            const typename G::cost_type edge_cost = e.info.get_val();
            out.push_back(make_shared<node_state<G>>(e.to, this->shared_from_this(), graph, cost + edge_cost));
        }
        return out;
    }
};
template<typename G, typename H>
requires Node_handler<H>
struct path {
    vector<H> path_handles;
    G graph;
    void set_graph (G g) {
        graph = g;
    }
    void print_path () {
        cout << "The path is " << endl;
        for (int i = 0; i < path_handles.size() - 1; i++) {
            cout << graph.handle_to_info(path_handles[i]).to_string();
            cout << " to ";
            cout << graph.handle_to_info(path_handles[i + 1]).to_string();
            cout << " ";
            cout << "cost is ";
            cout << graph.end_to_edge(path_handles[i], path_handles[i + 1]).to_string();
            cout << endl;
        }
        cout << endl;
    }
};
#endif