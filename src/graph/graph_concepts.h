#ifndef CGRAPH_CONCEPTS_H
#define CGRAPH_CONCEPTS_H
#include "graph.h"
using namespace std;
using namespace std_graph_lib;
template <typename T>
concept bool equality_comparable = 
requires (T t1, T t2) {
    {t1 == t2} -> bool;
    {t1 != t2} -> bool;
};
template <typename T>
concept bool comparable = 
requires (T t1, T t2) {
    requires equality_comparable<T>;
    {t1 > t2} -> bool;
    {t1 >= t2} -> bool;
    {t1 < t2} -> bool;
    {t1 <= t2} -> bool;
};
template <typename T>
concept bool numeric = 
requires (T t1, T t2) {
    {t1 + t2} -> T;
    {t1 - t2} -> T;
    {t1 * t2} -> T;
    {t1 / t2} -> T;
    {t1 % t2} -> T;
    {t1 << t2} -> T;
    {t1 >> t2} -> T;

    t1 = 0;

};
template <typename A, typename B>
concept bool same_type = 
requires (A a, B b) {
    {a} -> B;
    {b} -> A;
};
template <typename V>
concept bool Node_handler = 
requires (V v) {
    requires equality_comparable<V>;
};

template <typename E>
concept bool Edge_handler = 
requires (E e) {
    e.first;
    e.second;
    
};
template <typename I>
concept bool iterator = 
requires (I i) {
    {i.begin()} -> I;
    {i.end()} -> I;
    {i++} -> I;
};
template <typename S>
concept bool sequence = 
requires (S s) {
    typename S::value_type;
    typename S::iterator;
    {s.begin() } -> typename S::iterator;
    {s.end() } -> typename S::iterator;
};
template <typename G>
concept bool Graph = 
requires (G g, typename G::node_handle v) {
    typename G::node_handle;
    typename G::edge_handle;
    typename G::edge;
    typename G::out_edges::iterator;
    {g.out(v).begin()} -> typename G::out_edges::iterator;
    {g.out(v).end()} -> typename G::out_edges::iterator;
};

template <typename V>
concept bool Node_info = 
requires (V v) {
    {v.to_string() } -> string;
};

template <typename E>
concept bool Edge_info =
requires (E e1, E e2) {
    {e1.to_string() } -> string;
    {e1 + e2} -> E;
};
#endif