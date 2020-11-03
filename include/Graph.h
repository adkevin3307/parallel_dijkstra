#pragma once

#include <string>
#include <vector>

using namespace std;

class Edge {
public:
    Edge(int destination, int weight);
    ~Edge();

    int destination, weight;

    bool operator<(const Edge& edge)
    {
        if (this->weight != edge.weight) {
            return this->weight < edge.weight;
        }

        return this->destination < edge.destination;
    }
};

class Graph {
private:
    vector<vector<Edge>> _graph;

public:
    Graph(string path);
    ~Graph();

    size_t size();
    vector<Edge>& operator[](size_t index);
};