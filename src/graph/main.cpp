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
#include <fstream>
#include <string>
#include <sstream>
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

void load_map_data() {
    vector<vector<double>> vec;
    vector<string> cities;
    string line;
    string city_names;
    ifstream myfile ("./distance.csv");
    if (myfile.is_open())
    {
        getline (myfile,city_names);
        stringstream ss_cities(city_names);
        string city;
        while (getline(ss_cities, city, ',')) {
            cities.push_back(city);
        }

        while ( getline (myfile,line) )
        {
            vector<double> temp;
            stringstream ss(line);
            string item;
            while (getline(ss, item, ',')) {
                temp.push_back(std::stod(item));
            }
            vec.push_back(temp);
        }
        myfile.close();
    }

    fixed_directed_dense_graph<city, dis> city_map = fixed_directed_dense_graph<city, dis>(cities.size());

    vector<size_t> nodes;

    for (auto i = cities.begin(); i != cities.end(); ++i) {
        nodes.insert(nodes.begin(), city_map.insert_node(city(*i)));
    }

    for (int i = 0; i < cities.size(); ++i) {
        for (int j = 0; j < cities.size(); ++j) {
            city_map.insert_edge(nodes[i], nodes[j], dis(vec[i][j]));
        }
    }

    unordered_map<size_t, int> d;
    unordered_map<size_t, size_t> pi;

    shortest_path_bf(city_map, nodes[0], d, pi);

}

void test_shortest_path() {
    fixed_directed_dense_graph<city, dis> fddg = fixed_directed_dense_graph<city, dis>(6);
    auto s = fddg.insert_node(city("s"));
    auto t = fddg.insert_node(city("t"));
    auto a = fddg.insert_node(city("a"));
    auto b = fddg.insert_node(city("b"));
    auto c = fddg.insert_node(city("c"));
    auto f = fddg.insert_node(city("f"));
    auto e1 = fddg.insert_edge(s, a, dis(3));
    auto e2 = fddg.insert_edge(s, b, dis(4));
    auto e3 = fddg.insert_edge(a, c, dis(2));
    auto e4 = fddg.insert_edge(a, b, dis(6));
    auto e5 = fddg.insert_edge(a, f, dis(7));
    auto e6 = fddg.insert_edge(b, f, dis(5));
    auto e7 = fddg.insert_edge(c, f, dis(1));
    auto e8 = fddg.insert_edge(c, t, dis(8));
    auto e9 = fddg.insert_edge(f, t, dis(4));

    unordered_map<size_t, int> d;
    unordered_map<size_t, size_t> pi;

    shortest_path_bf(fddg, s, d, pi);
    cout << d[t] << endl;
}

int main() {

    fixed_dense_tests<fixed_directed_dense_graph<city, dis>, city, dis>();
    fixed_sparse_tests<fixed_directed_sparse_graph<city, dis>, city, dis>();
    dense_tests<directed_dense_graph<city, dis>, city, dis>();
    sparse_tests<directed_sparse_graph<city, dis>, city, dis>();
//    load_map_data();
    test_shortest_path();
}