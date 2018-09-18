#pragma once
#include<vector>
#include<stdio.h>
#include<stack>


/// Declare a graph presented by an adjacency matrix.
///  The number of vertices of the graph must be explicitly
/// initialized upon declaration. For example:
///  matrix_graph graph(20);
/// This declares and initializes a graph with 20 vertices.
class matrix_graph{
public:
    matrix_graph(const int&);
    void edge(const int&, const int&);
    void edge(const int&, const int&, const int&);
    void dedge(const int&, const int&);
    void dedge(const int&, const int&, const int&);
    void printMatrix() const;
    void printAdjList() const;
    void printConnComp() const;
    int connectedComponents();

    std::vector<int> dijkstra(const int&,const int&);
    bool isDirectional();
    bool isAcyclic();
    bool isDAG();
    void topoSort();
private:
    int size;
    matrix_graph();
    std::vector< std::vector<short int> > matrix;
};
