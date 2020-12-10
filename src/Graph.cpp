#include "Graph.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <climits>

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

    int total_edges = 0, min_edges = INT_MAX, max_edges = 0;
    for (size_t i = 0; i < this->_graph.size(); i++) {
        total_edges += this->_graph[i].size();

        min_edges = min(min_edges, (int)this->_graph[i].size());
        max_edges = max(max_edges, (int)this->_graph[i].size());

        sort(this->_graph[i].begin(), this->_graph[i].end());
    }

    cout << "Total nodes: " << nodes << '\n';
    cout << "Total edges: " << total_edges << '\n';
    cout << "Min edge numbers: " << min_edges << '\n';
    cout << "Max edge numbers: " << max_edges << '\n';
    cout << "Avg edge numbers: " << (total_edges / this->_graph.size()) << '\n';
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