
#include "Roy_Floyd_algorithm.h"

void print_path(vector<vector<int>>& next, int u, int v, fstream& myfile)
{
    vector<int> path;
    if (next[u][v] == -1)
        return;

    path.push_back(u);
    while (u != v)
    {
        u = next[u][v];
        path.push_back(u);
    }

    for (int i = 0; i < (int)path.size() - 1; i++)
    {
        myfile << path[i] << "->";
    }
    myfile << path[path.size() - 1] << endl;

}

vector<vector<int> > construct_next(vector<vector<int>> graph, int n)
{
    vector<vector<int>> next(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (graph[i][j] == INT_MAX)
                next[i][j] = -1;
            else
                next[i][j] = j;
        }
    }

    return next;
}

void floydWarshall(const Graph& graph, int idx, fstream& myfile)
{
    myfile.open("output_Roy_Floyd.txt", ios::out | ios::app);
    myfile << "< - - - - - - GRAPH " << idx << " - - - - - - > " << endl;

    std::chrono::high_resolution_clock::time_point start_point = std::chrono::high_resolution_clock::now();

    int n = graph.n;

    vector<vector<int> > next = construct_next(graph.adj_matrix, n);

    vector<vector<int>> dist = graph.adj_matrix;

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            std::chrono::high_resolution_clock::time_point end_point = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> time_span = end_point - start_point;
            std::cout << "Roy Floyd algorithm time : " << time_span.count() << " milliseconds.";
            std::cout << std::endl;


            myfile << "Graph contains negative weight cycle" << endl;
            myfile.close();
            return;
        }
    }

    std::chrono::high_resolution_clock::time_point end_point = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time_span = end_point - start_point;
    std::cout << "Roy Floyd algorithm time : " << time_span.count() << " milliseconds.";
    std::cout << std::endl;


    for (int src = 0; src < n; src++)
    {
        myfile << "Source : " << src << endl;
        for (int i = 0; i < n; i++)
        {
            if (dist[src][i] == INT_MAX) continue;
			myfile << src << " <-> " << i << " w : " << dist[src][i] << "  path : ";
			print_path(next, src, i, myfile);
        }
        myfile << endl;

    }
    myfile << endl;

    myfile.close();


}
