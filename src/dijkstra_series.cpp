#include <iostream>
#include <vector>
#include <climits>

#include "Graph.h"
#include "Timer.h"

using namespace std;

void show_path(vector<size_t>& parent)
{
    size_t index = parent.size() - 1;
    vector<size_t> nodes(1, index);

    while (parent[index] != index) {
        index = parent[index];

        nodes.push_back(index);
    }

    cout << "Shortest path: ";
    for (int i = nodes.size() - 1; i >= 0; i--) {
        cout << nodes[i] << (i == 0 ? "\n" : " -> ");
    }
}

int dijkstra(Graph& graph)
{
    vector<size_t> parent(graph.size(), 0);
    vector<bool> visit(graph.size(), false);
    vector<int> distance(graph.size(), INT_MAX / 2);

    distance[0] = 0;

    for (size_t i = 0; i < graph.size(); i++) {
        int source = -1;
        int min_distance = INT_MAX / 2;

        for (size_t j = 0; j < graph.size(); j++) {
            if (!visit[j] && distance[j] < min_distance) {
                source = j;
                min_distance = distance[j];
            }
        }

        if (source == -1) break;

        visit[source] = true;

        for (size_t j = 0; j < graph[source].size(); j++) {
            int destination = graph[source][j].destination;
            int weight = graph[source][j].weight;

            if (!visit[destination] && distance[source] + weight < distance[destination]) {
                distance[destination] = distance[source] + weight;
                parent[destination] = source;
            }
        }
    }

    // show_path(parent);

    return distance.back();
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: ./dijkstra_series {input file}" << '\n';

        return 0;
    }

    Graph graph(argv[1]);

    Timer::begin();
    int shortest_distance = dijkstra(graph);

    cout << "Shortest distance: " << shortest_distance << '\n';
    Timer::end();

    cout << "Execution time: " << Timer::time() << '\n';

    return 0;
}