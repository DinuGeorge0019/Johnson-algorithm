#pragma once
#include "graph.h"

void print_path(vector<int> parent, int dest, fstream& myfile);
vector<int> Bellman_Ford(vector<Edge> edges, int n);
void Dijkstra(vector<vector<int>> graph, int src, fstream& myfile);
void Johnson_algorithm(Graph graph, int idx, fstream& myfile);