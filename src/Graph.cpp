#include "Graph.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Edge::Edge(int destination, int weight)
{
    this->destination = destination;
    this->weight = weight;
}

Edge::~Edge()
{
}

Graph::Graph()
{
}

Graph::Graph(string path)
{
    fstream file;
    file.open(path, ios::in);

    int nodes;
    file >> nodes;
    this->_graph.resize(nodes);

    int source, destination, weight;
    while (file >> source >> destination >> weight) {
        this->_graph[source].push_back(Edge(destination, weight));
    }

    file.close();

    for (size_t i = 0; i < this->_graph.size(); i++) {
        sort(this->_graph[i].begin(), this->_graph[i].end());
    }

    cout << "Total nodes: " << nodes << '\n';
}

Graph::~Graph()
{
    for (auto node : this->_graph) {
        node.clear();
    }

    this->_graph.clear();
}

size_t Graph::size()
{
    return this->_graph.size();
}

vector<Edge>& Graph::operator[](size_t index)
{
    if (index < this->_graph.size()) {
        return this->_graph[index];
    }

    throw out_of_range("Index out of range");
}