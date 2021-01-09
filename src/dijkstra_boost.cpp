#define BOOST_ALLOW_DEPRECATED_HEADERS

#include <iostream>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

#include "Graph.h"
#include "Timer.h"

using namespace std;

typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> graph_t;
typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

void show_path(vector<vertex_descriptor>& parent)
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

int dijkstra(graph_t& graph)
{
    vector<vertex_descriptor> parent(num_vertices(graph));
    vector<int> distance(num_vertices(graph));
    vertex_descriptor source = vertex(0, graph);

    boost::dijkstra_shortest_paths(
        graph, source, boost::predecessor_map(
            boost::make_iterator_property_map(
                parent.begin(), boost::get(boost::vertex_index, graph)
            )
        ).distance_map(
            boost::make_iterator_property_map(
                distance.begin(), boost::get(boost::vertex_index, graph)
            )
        )
    );

    // show_path(parent);

    return distance.back();
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: ./dijkstra_boost {input file}" << '\n';

        return 0;
    }

    Graph graph(argv[1]);

    vector<pair<int, int>> edges;
    vector<int> weights;

    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = 0; j < graph[i].size(); j++) {
            edges.push_back(make_pair(i, graph[i][j].destination));
            weights.push_back(graph[i][j].weight);
        }
    }

    graph_t graph_(edges.begin(), edges.end(), &weights[0], graph.size());

    Timer::begin();
    int shortest_distance = dijkstra(graph_);

    cout << "Shortest distance: " << shortest_distance << '\n';
    Timer::end();

    cout << "Execution time: " << Timer::time() << '\n';

    return 0;
}
