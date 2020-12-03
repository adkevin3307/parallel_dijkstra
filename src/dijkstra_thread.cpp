#include <iostream>
#include <vector>
#include <climits>
#include <thread>

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

void search(vector<bool>& visit, vector<int>& distance, int begin, int step, int end, int& source)
{
    int local_source = -1;
    int local_min_distance = INT_MAX / 2;

    for (int i = begin; i < end; i += step) {
        if (!visit[i] && distance[i] < local_min_distance) {
            local_source = i;
            local_min_distance = distance[i];
        }
    }

    source = local_source;
}

void compare(int id_1, int id_2, vector<int>& sources, vector<int>& distance)
{
    int distance_1 = (sources[id_1] == -1 ? INT_MAX / 2 : distance[sources[id_1]]);
    int distance_2 = (sources[id_2] == -1 ? INT_MAX / 2 : distance[sources[id_2]]);

    if (distance_1 > distance_2) {
        sources[id_1] = sources[id_2];
    }
}

void update(Graph& graph, vector<bool>& visit, vector<int>& distance, vector<size_t>& parent, int source, int begin, int step, int end)
{
    for (int i = begin; i < end; i += step) {
        int destination = graph[source][i].destination;
        int weight = graph[source][i].weight;

        if (!visit[destination] && distance[source] + weight < distance[destination]) {
            distance[destination] = distance[source] + weight;
            parent[destination] = source;
        }
    }
}

int dijkstra(Graph& graph, int thread_amount)
{
    vector<size_t> parent(graph.size(), 0);
    vector<bool> visit(graph.size(), false);
    vector<int> distance(graph.size(), INT_MAX / 2);

    distance[0] = 0;

    thread_amount = ((int)graph.size() < thread_amount ? graph.size() : thread_amount);
    cout << "thread amount: " << thread_amount << '\n';

    vector<thread> threads(thread_amount);
    vector<int> sources(thread_amount);

    for (size_t i = 0; i < graph.size(); i++) {
        for (auto id = 0; id < thread_amount; id++) {
            threads[id] = thread(search, ref(visit), ref(distance), id, thread_amount, graph.size(), ref(sources[id]));
        }

        for (auto id = 0; id < thread_amount; id++) {
            threads[id].join();
        }

        int index = thread_amount;
        while (index > 1) {
            if (index % 2) {
                compare(0, index - 1, sources, distance);
            }

            for (auto id = 0; id < index / 2; id++) {
                threads[id] = thread(compare, id, id + index / 2, ref(sources), ref(distance));
            }

            for (auto id = 0; id < index / 2; id++) {
                threads[id].join();
            }

            index /= 2;
        }

        int source = sources[0];

        if (source == -1) break;

        visit[source] = true;

        for (auto id = 0; id < thread_amount; id++) {
            threads[id] = thread(update, ref(graph), ref(visit), ref(distance), ref(parent), source, id, thread_amount, graph[source].size());
        }

        for (auto id = 0; id < thread_amount; id++) {
            threads[id].join();
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
    int shortest_distance = dijkstra(graph, 12);

    cout << "Shortest distance: " << shortest_distance << '\n';
    Timer::end();

    cout << "Execution time: " << Timer::time() << '\n';

    return 0;
}
