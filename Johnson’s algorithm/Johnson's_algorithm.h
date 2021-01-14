#pragma once
#include "graph.h"

void print_path(vector<int>& parent, int dest, fstream& myfile, vector<vector<pair<int, int>>> old_graph);
vector<int> Bellman_Ford(vector<Edge> edges, int n);
void Dijkstra(vector<vector<pair<int, int>>> adj_list, int src, fstream& myfile, vector<vector<pair<int, int>>> old_graph, chrono::high_resolution_clock::time_point& start_point, chrono::high_resolution_clock::time_point& end_point);
void Johnson_algorithm(const Graph& graph, int idx, fstream& myfile);