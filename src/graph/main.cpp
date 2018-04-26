#include <iostream>
#include "graph.h"
#include "user_structs.h"
#include "path_structs.h"
#include "algorithms.h"
#include "fixed_directed_sparse_graph_lib.h"
#include "fixed_directed_dense_graph_lib.h"
#include "directed_dense_graph_lib.h"
#include "directed_sparse_graph_lib.h"
#include "graph_concepts.h"
using namespace std;
using namespace std_graph_lib;
template <typename G, typename V, typename E>
requires Graph<G> && Node_info<V> && Edge_info<E>
void fixed_dense_tests() {

    fixed_directed_dense_graph<V, E> fddg = fixed_directed_dense_graph<V, E>(6);
    auto v0 = fddg.insert_node(city("New York"));
    auto v1 = fddg.insert_node(city("San Francisco"));
    auto v2 = fddg.insert_node(city("Los Angeles"));
    auto v3 = fddg.insert_node(city("Chicago"));
    auto v4 = fddg.insert_node(city("Seattle"));
    auto v5 = fddg.insert_node(city("Houston"));
    auto e1 = fddg.insert_edge(v0, v1, dis(2914));
    auto e2 = fddg.insert_edge(v3, v4, dis(2066));
    auto e3 = fddg.insert_edge(v1, v3, dis(2130));
    auto e4 = fddg.insert_edge(v0, v2, dis(2793));
    auto e5 = fddg.insert_edge(v2, v3, dis(2016));
    for (const auto& node : fddg.all_nodes()) {
        cout << node << endl;
    }
    fddg.print_graph();
    shared_ptr<path<G, typename G::node_handle>> bfs_path = bfs_findpath(fddg, v0, v3);
    bfs_path->print_path();
    shared_ptr<path<G, typename G::node_handle>> dfs_path = dfs_findpath(fddg, v0, v3);
    dfs_path->print_path();
    //cout << dfs_findpath(fddg, v0, v1) << endl;

}
template<typename G, typename V, typename E>
requires Graph<G> && Node_info<V> && Edge_info<E>
void fixed_sparse_tests() {

    fixed_directed_sparse_graph<V, E> fdsg = fixed_directed_sparse_graph<V, E>(6);
    auto v0 = fdsg.insert_node(city("New York"));
    auto v1 = fdsg.insert_node(city("San Francisco"));
    auto v2 = fdsg.insert_node(city("Los Angeles"));
    auto v3 = fdsg.insert_node(city("Chicago"));
    auto v4 = fdsg.insert_node(city("Seattle"));
    auto v5 = fdsg.insert_node(city("Houston"));
    auto e1 = fdsg.insert_edge(v0, v1, dis(2914));
    auto e2 = fdsg.insert_edge(v3, v4, dis(2066));
    auto e3 = fdsg.insert_edge(v1, v3, dis(2130));
    auto e4 = fdsg.insert_edge(v0, v2, dis(2793));
    auto e5 = fdsg.insert_edge(v2, v3, dis(2016));
    for (const auto& node : fdsg.all_nodes()) {
        cout << node << endl;
    }
    fdsg.print_graph();
    shared_ptr<path<G, typename G::node_handle>> bfs_path = bfs_findpath(fdsg, v0, v3);
    bfs_path->print_path();
    shared_ptr<path<G, typename G::node_handle>> dfs_path = dfs_findpath(fdsg, v0, v3);
    dfs_path->print_path();

}
template <typename G, typename V, typename E>
requires Graph<G> && Node_info<V> && Edge_info<E>
void dense_tests() {

    directed_dense_graph<V, E> ddg = directed_dense_graph<V, E>();
    auto v0 = ddg.insert_node(city("New York"));
    auto v1 = ddg.insert_node(city("San Francisco"));
    auto v2 = ddg.insert_node(city("Los Angeles"));
    auto v3 = ddg.insert_node(city("Chicago"));
    auto v4 = ddg.insert_node(city("Seattle"));
    auto v5 = ddg.insert_node(city("Houston"));
    auto e1 = ddg.insert_edge(v0, v1, dis(2914));
    auto e2 = ddg.insert_edge(v3, v4, dis(2066));
    auto e3 = ddg.insert_edge(v1, v3, dis(2130));
    auto e4 = ddg.insert_edge(v0, v2, dis(2793));
    auto e5 = ddg.insert_edge(v2, v3, dis(2016));
    for (const auto& node : ddg.all_nodes()) {
        cout << node << endl;
    }
    ddg.print_graph();
    shared_ptr<path<G, typename G::node_handle>> bfs_path = bfs_findpath(ddg, v0, v3);
    bfs_path->print_path();
    shared_ptr<path<G, typename G::node_handle>> dfs_path = dfs_findpath(ddg, v0, v3);
    dfs_path->print_path();
    ddg.erase_node(v3);
    for (const auto& node : ddg.all_nodes()) {
        cout << node << endl;
    }
    ddg.print_graph();

}

template <typename G, typename V, typename E>
requires Graph<G> && Node_info<V> && Edge_info<E>
void sparse_tests() {

    directed_sparse_graph<V, E> dsg = directed_sparse_graph<V, E>();
    auto v0 = dsg.insert_node(city("New York"));
    auto v1 = dsg.insert_node(city("San Francisco"));
    auto v2 = dsg.insert_node(city("Los Angeles"));
    auto v3 = dsg.insert_node(city("Chicago"));
    auto v4 = dsg.insert_node(city("Seattle"));
    auto v5 = dsg.insert_node(city("Houston"));
    auto e1 = dsg.insert_edge(v0, v1, dis(2914));
    auto e2 = dsg.insert_edge(v3, v4, dis(2066));
    auto e3 = dsg.insert_edge(v1, v3, dis(2130));
    auto e4 = dsg.insert_edge(v0, v2, dis(2793));
    auto e5 = dsg.insert_edge(v2, v3, dis(2016));
    for (const auto& node : dsg.all_nodes()) {
        cout << node << endl;
    }
    dsg.print_graph();
    shared_ptr<path<G, typename G::node_handle>> bfs_path = bfs_findpath(dsg, v0, v3);
    bfs_path->print_path();
    shared_ptr<path<G, typename G::node_handle>> dfs_path = dfs_findpath(dsg, v0, v3);
    dfs_path->print_path();
    dsg.erase_node(v3);
    for (const auto& node : dsg.all_nodes()) {
        cout << node << endl;
    }
    dsg.print_graph();

}
int main() {
    
    fixed_dense_tests<fixed_directed_dense_graph<city, dis>, city, dis>();
    fixed_sparse_tests<fixed_directed_sparse_graph<city, dis>, city, dis>();
    dense_tests<directed_dense_graph<city, dis>, city, dis>();
    sparse_tests<directed_sparse_graph<city, dis>, city, dis>();
}