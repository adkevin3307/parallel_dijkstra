#include <iostream>
#include <vector>
#include <climits>
#include <omp.h>
#include <algorithm>

#include "Graph.h"

#define MAX_THREAD_NUM
using namespace std;

void show_path(vector<size_t> &parent)
{
    size_t index = parent.size() - 1;
    vector<size_t> nodes(1, index);

    while (parent[index] != index)
    {
        index = parent[index];

        nodes.push_back(index);
    }

    cout << "Shortest path: ";
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        cout << nodes[i] << (i == 0 ? "\n" : " -> ");
    }
}

int dijkstra(Graph &graph)
{
    vector<size_t> parent(graph.size(), 0);
    vector<bool> visit(graph.size(), false);
    vector<int> distance(graph.size(), INT_MAX/2 );
    vector<int> localMinDistanceNode(8, 0);
    distance[0] = 0;
    for (size_t i = 0; i < graph.size(); i++)
    {
        int curLocalMinDistanceNodeLen;
#pragma omp parallel
        {
            int source = -1;
            int min_distance = INT_MAX/2 ;

            //comput local minimal distance
#pragma omp for
            for (size_t j = 0; j < graph.size(); j++)
            {
                if (!visit[j] && distance[j] < min_distance)
                {
                    source = j;
                    min_distance = distance[j];
                }
            }
            localMinDistanceNode[omp_get_thread_num()] = source;
#pragma omp single
            {
                curLocalMinDistanceNodeLen = omp_get_num_threads();
            }
        }
        //compute global minimal distances
        while (curLocalMinDistanceNodeLen > 1)
        {
            //consider len is odd
            if (curLocalMinDistanceNodeLen % 2 == 1)
            {
                if (localMinDistanceNode[0] == -1)
                    localMinDistanceNode[0] = localMinDistanceNode.back();
                else if (localMinDistanceNode.back() == -1)
                    localMinDistanceNode[0] = localMinDistanceNode[0];
                else
                {
                    localMinDistanceNode[0] = distance[0] <
                                                      distance[localMinDistanceNode.back()]
                                                  ? localMinDistanceNode[0]
                                                  : localMinDistanceNode.back();
                }
            }
#pragma omp parallel for
            for (int i = 0; i < curLocalMinDistanceNodeLen / 2; i++)
            {
                int curThreadIndex = omp_get_thread_num();
                int secondNodeIndex = curThreadIndex + curLocalMinDistanceNodeLen / 2;
                if (localMinDistanceNode[curThreadIndex] == -1)
                    localMinDistanceNode[curThreadIndex] = localMinDistanceNode[secondNodeIndex];
                else if (localMinDistanceNode[secondNodeIndex] == -1)
                    localMinDistanceNode[curThreadIndex] = localMinDistanceNode[curThreadIndex];
                else
                {
                    localMinDistanceNode[curThreadIndex] = distance[localMinDistanceNode[curThreadIndex]] <
                                                                   distance[localMinDistanceNode[secondNodeIndex]]
                                                               ? localMinDistanceNode[curThreadIndex]
                                                               : localMinDistanceNode[secondNodeIndex];
                }
            }
            curLocalMinDistanceNodeLen /= 2;
        }
        int source = localMinDistanceNode[0];

        if (source == -1)
            break;

        visit[source] = true;

        // update distances
        #pragma omp parallel for
        for (size_t j = 0; j < graph[source].size(); j++)
        {
            int destination = graph[source][j].destination;
            int weight = graph[source][j].weight;

            if (!visit[destination] && distance[source] + weight < distance[destination])
            {
                distance[destination] = distance[source] + weight;
                parent[destination] = source;
            }
        }
    }

    show_path(parent);

    return distance.back();
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: ./dijkstra_series {input file}" << '\n';

        return 0;
    }

    Graph graph(argv[1]);
    int shortest_distance = dijkstra(graph);

    cout << "Shortest distance: " << shortest_distance << '\n';

    return 0;
}
