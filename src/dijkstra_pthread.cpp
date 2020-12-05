#include <iostream>
#include <vector>
#include <climits>
#include <pthread.h>

#include "Graph.h"
#include "Timer.h"

using namespace std;

Graph graph;
int thread_amount;

vector<size_t> _parent;
vector<bool> _visit;
vector<int> _distance;
int source;

pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct search_parameter {
    int id, begin, step, end;
};

void show_path()
{
    size_t index = _parent.size() - 1;
    vector<size_t> nodes(1, index);

    while (_parent[index] != index) {
        index = _parent[index];

        nodes.push_back(index);
    }

    cout << "Shortest path: ";
    for (int i = nodes.size() - 1; i >= 0; i--) {
        cout << nodes[i] << (i == 0 ? "\n" : " -> ");
    }
}

void* execute(void* parameter)
{
    search_parameter* args = (search_parameter*)parameter;

    int local_source = -1;
    int local_min_distance = INT_MAX / 2;

    for (int i = args->begin; i < args->end; i += args->step) {
        if (!_visit[i] && _distance[i] < local_min_distance) {
            local_source = i;
            local_min_distance = _distance[i];
        }
    }

    pthread_mutex_lock(&mutex);
    int min_distance = (source == -1 ? INT_MAX / 2 : _distance[source]);

    if (local_min_distance < min_distance) {
        source = local_source;
    }
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    if (source == -1) return NULL;

    _visit[source] = true;

    for (size_t i = args->begin; i < graph[source].size(); i += args->step) {
        int destination = graph[source][i].destination;
        int weight = graph[source][i].weight;

        if (!_visit[destination] && _distance[source] + weight < _distance[destination]) {
            _distance[destination] = _distance[source] + weight;
            _parent[destination] = source;
        }
    }

    pthread_barrier_wait(&barrier);

    return NULL;
}

int dijkstra(Graph& graph)
{
    int node = graph.size();

    _parent = vector<size_t>(node, 0);
    _visit = vector<bool>(node, false);
    _distance = vector<int>(node, INT_MAX / 2);

    _distance[0] = 0;

    cout << "thread amount: " << thread_amount << '\n';

    vector<search_parameter> parameters(thread_amount);

    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, thread_amount);

    for (auto id = 0; id < thread_amount; id++) {
        parameters[id].id = id;
        parameters[id].begin = id;
        parameters[id].step = thread_amount;
        parameters[id].end = node;
    }

    for (auto i = 0; i < node; i++) {
        source = -1;

        for (auto id = 1; id < thread_amount; id++) {
            pthread_t thread;
            pthread_create(&(thread), NULL, execute, &(parameters[id]));
            pthread_detach(thread);
        }

        execute(&(parameters[0]));
    }

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    // show_path();

    return _distance.back();
}

int main(int argc, char** argv)
{
    if (argc != 2 && argc != 3) {
        cerr << "Usage: ./dijkstra_series {input file} {thread num=8}" << '\n';

        return 0;
    }

    graph = Graph(argv[1]);
    thread_amount = (argc == 2 ? 8 : atoi(argv[2]));

    Timer::begin();
    int shortest_distance = dijkstra(graph);

    cout << "Shortest distance: " << shortest_distance << '\n';
    Timer::end();

    cout << "Execution time: " << Timer::time() << '\n';

    return 0;
}
