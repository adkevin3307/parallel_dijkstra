#include <iostream>
#include <vector>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

#include "Graph.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: ./dijkstra_series {input file}" << '\n';

        return 0;
    }

    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> graph_t;
    typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

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

    vector<vertex_descriptor> parent(num_vertices(graph_));
    vector<int> distance(num_vertices(graph_));
    vertex_descriptor source = vertex(0, graph_);

    boost::dijkstra_shortest_paths(
        graph_, source, boost::predecessor_map(
            boost::make_iterator_property_map(
                parent.begin(), boost::get(boost::vertex_index, graph_)
            )
        ).distance_map(
            boost::make_iterator_property_map(
                distance.begin(), boost::get(boost::vertex_index, graph_)
            )
        )
    );

    cout << "Shortest distance: " << distance[graph.size() - 1] << '\n';

    return 0;
}