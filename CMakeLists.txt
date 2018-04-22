cmake_minimum_required(VERSION 3.10)
project(CGraph)

set(CMAKE_CXX_STANDARD 11)

add_library(CGraph library.cpp library.h src/graph/Edge.h src/graph/DefaultEdge.h src/graph/WeightedEdge.h src/graph/Graph.h src/graph/Vertex.h src/graph/fixed_directed_sparse_graph_lib.h src/graph/fixed_directed_dense_graph_lib.h)