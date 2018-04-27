#ifndef CGRAPH_ALGORITHMS_H
#define CGRAPH_ALGORITHMS_H
#include "graph.h"
#include "graph_concepts.h"
#include "path_structs.h"
#include <memory>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <limits>
using namespace std;
using namespace std_graph_lib;

int null_prev = -1;

template<typename G, typename MP>
void dijstra(G g, typename G::node_handle s, MP& mp) {
    priority_queue<pair<typename MP::mapped_type, typename G::node_handle> > que;
    que.push({0, s});
    while (!que.empty()) {
        auto [dis, v] = que.top(); 
        mp[v] = dis;
        que.pop();
        for (auto& e: g.out(v)) {
            if (!mp.count(e.to)) {
                que.push(dis + e.info, e.to);
            }
        }
    }
}
template <typename G, typename C>
requires Graph<G>
bool generic_pathexists(G g, typename G::node_handle s, typename G::node_handle e, C& container) {
    bool flag = false;
    //int node_num = g.node_cnt();
    unordered_map<typename G::node_handle, bool> visited;
    container.push(s);
    while (!container.empty()) {
        auto v = container.top();
        container.pop();
        // find the end
        if (v == e) {
            return true;
        }
        visited[v] = true;
        for (const auto& e: g.out(v)) {
            const auto to = e.to;
            if (!visited[to]) container.push(to);
        }
    }
    return false;
}
template <typename T>
class _queue: public queue<T> {
public:
    const T& top() {
        return this->front();
    }
};
template<typename G>
requires Graph<G>
bool bfs_pathexists(G g, typename G::node_handle s, typename G::node_handle e) {
    _queue<typename G::node_handle> q;
    return generic_pathexists(g, s, e, q);
}
template<typename G>
requires Graph<G>
bool dfs_pathexists(G g, typename G::node_handle s, typename G::node_handle e) {
    stack<typename G::node_handle> q;
    return generic_pathexists(g, s, e, q);
}

template<typename G>
requires Graph<G>
shared_ptr<path<G, typename G::node_handle>> bfs_findpath(G g, typename G::node_handle s, typename G::node_handle e) {
    _queue<shared_ptr<node_state<G>>> node_states;
    return generic_findpath(g, s, e, node_states);
}

template<typename G>
requires Graph<G>
shared_ptr<path<G, typename G::node_handle>> dfs_findpath(G g, typename G::node_handle s, typename G::node_handle e) {
    stack<shared_ptr<node_state<G>>> node_states;
    return generic_findpath(g, s, e, node_states);
}
template<typename G, typename C>
requires Graph<G>
shared_ptr<path<G, typename G::node_handle>> generic_findpath(G g, typename G::node_handle s, typename G::node_handle e, C& container) {
    using node_handle = typename G::node_handle;
    unordered_map<node_handle, bool> visited;
    //container for states
    shared_ptr<node_state<G>> start = make_shared<node_state<G>>(s, nullptr, g, 0); 
    container.push(start);
    while (!container.empty()) {
        auto v = container.top();
        container.pop();
        //cout << v->handle << endl;
        //cout << v->cost.to_string() << endl;
        if (v->handle == e) {
            //backtrack path
            vector<node_handle> node_handles;
            //vector<V> node_infos;
            // push this node's info into queue
            node_handles.push_back(e);
            //node_infos.push_back(g.handle_to_info(e));
            //cout << v->cost.to_string() << endl;
            // backtrack
            v = v->parent;
            while (v != nullptr) {
                //cout << v->handle << endl;
                node_handles.push_back(v->handle);
                
                //node_infos.push_back(g.handle_to_info(v->handle));
                v = v -> parent;
            }
            reverse(node_handles.begin(), node_handles.end());
            shared_ptr<path<G, node_handle>> found_path = make_shared<path<G, node_handle>>();
            found_path->path_handles = node_handles;
            found_path->set_graph(g);
            return found_path;

        } else {
            vector<shared_ptr<node_state<G>>> out_states = v->out_states();
            for (const auto& state: out_states) {
                //cout << v->handle << state->handle << endl;
                if (!visited[state->handle]) {
                    container.push(state);
                }
            }
            visited[v->handle] = true;
        }
    }
    shared_ptr<path<G, node_handle>> found_path = make_shared<path<G, node_handle>>();
    vector<node_handle> node_handles;
    found_path->path_handles = node_handles;
    return found_path;
}

template<typename G>
requires Graph<G>
void relax(G g, typename G::node_handle u, typename G::node_handle v,
           unordered_map<typename G::node_handle, int>& d,
           unordered_map<typename G::node_handle, typename G::node_handle>& pi){
    auto weight = g.end_to_edge(u, v).get_val();
    if (d[v] > d[u] + weight){
        d[v] = d[u] + weight;
        pi[v] = u;
    }
}

template<typename G>
requires Graph<G>
void shortest_path_bf(G g, typename G::node_handle s,
                      unordered_map<typename G::node_handle, int>& d,
                      unordered_map<typename G::node_handle, typename G::node_handle>& pi){
    for (auto v: g.all_nodes()) {
        d[v] = std::numeric_limits<int>::max();
        pi[v] = -1;
    }
    d[s] = 0;

    for (auto v: g.all_nodes()) {
        for (auto v2: g.all_nodes()) {
            for (const auto& e: g.out(v2)) {
                if (d[e.to] > d[v2] + e.info.get_val()){
                    d[e.to] = d[v2] + e.info.get_val();
                    pi[e.to] = v2;
                }
            }
        }
    }
}

template<typename G>
requires Graph<G>
void print_path(G g, typename G::node_handle s, typename G::node_handle t,
                      unordered_map<typename G::node_handle, typename G::node_handle>& pi){
    string path = g.handle_to_info(t).to_string();
    while(pi[t]!= null_prev) {
        t = pi[t];
        path = g.handle_to_info(t).to_string() + " " + path;
    }

    cout << path << endl;
}


//template<typename G>
//requires Graph<G>
//void get_path(typename G::node_handle s, typename G::node_handle t,
//              unordered_map<typename G::node_handle, typename G::node_handle>& pi) {
//
//}
//
//template<typename G>
//requires Graph<G>
//void apsp_johnson(G g) {
//    unordered_map<typename G::node_handle, double>& d;
//    unordered_map<typename G::node_handle, typename G::node_handle>& pi;
//    shortest_path_bf(g, g.vertex);
//
//    unordered_map<typename G::node_handle, double> p;
//    for (node_handle v: Vertices) {
//        p[v] = - d[v];
//    }
//
//
//}



#endif
