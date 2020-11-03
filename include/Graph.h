#pragma once

#include <string>
#include <vector>

using namespace std;

class Edge {
public:
    Edge(int destination, int weight);
    ~Edge();

    int destination, weight;

    friend bool operator<(const Edge& a, const Edge& b)
    {
        if (a.weight != b.weight) {
            return a.weight < b.weight;
        }

        return a.destination < b.destination;
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