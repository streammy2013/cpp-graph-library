#include <iostream>
#include "graph.h"
#include "user_structs.h"
#include "algorithms.h"
#include "fixed_directed_sparse_graph_lib.h"
#include "fixed_directed_dense_graph_lib.h"
#include "directed_dense_graph_lib.h"
#include "directed_sparse_graph_lib.h"
using namespace std;
using namespace std_graph_lib;
template <typename G, typename V, typename E>
void fixed_dense_tests() {

    fixed_directed_dense_graph<V, E> fddg = fixed_directed_dense_graph<V, E>(6);
    auto v0 = fddg.insert_node(city("New York"));
    auto v1 = fddg.insert_node(city("San Francisco"));
    auto vv2 = fddg.insert_node(city("Los Angeles"));
    auto vv3 = fddg.insert_node(city("Chicago"));
    auto vv4 = fddg.insert_node(city("Seattle"));
    auto vv5 = fddg.insert_node(city("Houston"));
    auto ee1 = fddg.insert_edge(v0, v1, dis(2914));
    auto ee2 = fddg.insert_edge(vv3, vv4, dis(2066));
    fddg.print_graph();
    cout << bfs_findpath(fddg, v0, v1) << endl;
    cout << dfs_findpath(fddg, v0, v1) << endl;

}
template<typename G, typename V, typename E>
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
    fdsg.print_graph();
    cout << bfs_findpath(fdsg, v0, v1) << endl;
    cout << dfs_findpath(fdsg, v0, v1) << endl;

}
template <typename G, typename V, typename E>
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
    ddg.print_graph();
    ddg.erase_node(v3);
    ddg.print_graph();
    cout << bfs_findpath(ddg, v0, v1) << endl;
    cout << dfs_findpath(ddg, v0, v1) << endl;
    cout << bfs_findpath(ddg, v5, v4) << endl;
    cout << dfs_findpath(ddg, v5, v4) << endl;

}

template <typename G, typename V, typename E>
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
    dsg.print_graph();
    dsg.erase_node(v3);
    dsg.print_graph();
    cout << bfs_findpath(dsg, v0, v1) << endl;
    cout << dfs_findpath(dsg, v0, v1) << endl;
    cout << bfs_findpath(dsg, v5, v4) << endl;
    cout << dfs_findpath(dsg, v5, v4) << endl;

}
int main() {
    
    fixed_dense_tests<fixed_directed_dense_graph<city, dis>, city, dis>();
    fixed_sparse_tests<fixed_directed_sparse_graph<city, dis>, city, dis>();
    dense_tests<directed_dense_graph<city, dis>, city, dis>();
    sparse_tests<directed_sparse_graph<city, dis>, city, dis>();
}