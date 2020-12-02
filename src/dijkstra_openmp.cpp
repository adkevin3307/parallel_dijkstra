#include <iostream>
#include <vector>
#include <climits>
#include <omp.h>
#include <algorithm>

#include "Graph.h"

#define threadNum 8

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

int dijkstra(Graph &graph,int numOfThread)
{
    vector<size_t> parent(graph.size(), 0);
    vector<bool> visit(graph.size(), false);
    vector<int> distance(graph.size(), INT_MAX/2 );
    vector<int> localMinDistanceNode(numOfThread, 0);
    //cout << "numofthread " << numOfThread << "localMinDistanceNodesize" << localMinDistanceNode.size() << endl;
    distance[0] = 0;
    for (size_t i = 0; i < graph.size(); i++)
    {
        //cout << "!!!!!!!!!!!!!!!!!!new iter index " << i << endl;
        int curLocalMinDistanceNodeLen;
        omp_set_num_threads(numOfThread);
#pragma omp parallel
        {
            int source = -1;
            if(i==0&&omp_get_thread_num() == 0) cout << "actual thread num" << omp_get_num_threads() << endl;
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
        /*
        cout <<"loop index" << i<< "-------localMinDistanceNode------" << endl;
        for(int j=0;j<localMinDistanceNode.size();j++){
            cout << "index" << j <<localMinDistanceNode[j]  << " ";
        }
        cout << endl;
        */
        //compute global minimal distances
        while (curLocalMinDistanceNodeLen > 1)
        {
            //consider len is odd
            if (curLocalMinDistanceNodeLen % 2 == 1)
            {
                //cout << "curLocalMindistanceNodeLen is odd" << endl;
                if (localMinDistanceNode[0] == -1)
                    localMinDistanceNode[0] = localMinDistanceNode[curLocalMinDistanceNodeLen-1];
                else if (localMinDistanceNode[curLocalMinDistanceNodeLen-1] == -1 ){

                }
                else
                {
                    localMinDistanceNode[0] = distance[localMinDistanceNode [0]] <
                                                      distance[localMinDistanceNode [curLocalMinDistanceNodeLen-1]]
                                                  ? localMinDistanceNode[0]
                                                  : localMinDistanceNode[curLocalMinDistanceNodeLen-1];
                }
                /*
                cout <<"loop index" << i<< "-------localMinDistanceNode------" << endl;
                for(int j=0;j<localMinDistanceNode.size();j++){
                    cout << "index" << j <<localMinDistanceNode[j]  << " ";
                }
        cout << endl;
                */
            }
        omp_set_num_threads(numOfThread);
#pragma omp parallel for
            for (int j = 0; j < curLocalMinDistanceNodeLen / 2; j++)
            {
                int curThreadIndex = omp_get_thread_num();
                int secondNodeIndex = curThreadIndex + curLocalMinDistanceNodeLen / 2;
                if (localMinDistanceNode[curThreadIndex] == -1)
                    localMinDistanceNode[curThreadIndex] = localMinDistanceNode[secondNodeIndex];
                else if (localMinDistanceNode[secondNodeIndex] == -1){

                }
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
        /*
        cout <<"loop index" << i<< "-------localMinDistanceNode------" << endl;
        for(int j=0;j<localMinDistanceNode.size();j++){
            cout << "index" << j <<localMinDistanceNode[j]  << " ";
        }
        cout << endl;
        */
        int source = localMinDistanceNode[0];
        //cout << " source " << source << endl;

        if (source == -1)
            break;

        visit[source] = true;

        // update distances
        omp_set_num_threads(numOfThread);
        #pragma omp parallel for
        for (size_t j = 0; j < graph[source].size(); j++)
        {
            //if(j==0 && omp_get_thread_num () == 0) cout << "actual thread num" << omp_get_num_threads() << endl;
            int destination = graph[source][j].destination;
            int weight = graph[source][j].weight;

            if (!visit[destination] && distance[source] + weight < distance[destination])
            {
                distance[destination] = distance[source] + weight;
                parent[destination] = source;
            }
        }
    }

    // show_path(parent);

    return distance.back();
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cerr << "Usage: ./dijkstra_series {input file} {threadNu}" << '\n';

        return 0;
    }
    int numofThread= atoi(argv[2]);
    Graph graph(argv[1]);
    int shortest_distance = dijkstra(graph,numofThread);

    cout << "Shortest distance: " << shortest_distance << '\n';

    return 0;
}
