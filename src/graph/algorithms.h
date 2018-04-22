#ifndef CGRAPH_ALGORITHMS_H
#define CGRAPH_ALGORITHMS_H
#include "graph.h"
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std_graph_lib;

template<typename G, typename MP>
void dijstra(G g, node_handle s, MP& mp) {
    priority_queue<pair<typename MP::mapped_type, node_handle> > que;
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
bool generic_pathexists(G g, node_handle s, node_handle e, C& container) {
    bool flag = false;
    int node_num = g.node_cnt();
    unordered_map<node_handle, bool> visited;
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
bool bfs_findpath(G g, node_handle s, node_handle e) {
    _queue<node_handle> q;
    return generic_pathexists(g, s, e, q);
}
template<typename G>
bool dfs_findpath(G g, node_handle s, node_handle e) {
    stack<node_handle> q;
    return generic_pathexists(g, s, e, q);
}

#endif