cmake_minimum_required(VERSION 3.10)
project(CGraph)

set(CMAKE_CXX_STANDARD 11)

add_library(CGraph library.cpp library.h src/graph/Edge.h src/graph/DefaultEdge.h src/graph/WeightedEdge.h src/graph/Graph.h src/graph/Vertex.h)