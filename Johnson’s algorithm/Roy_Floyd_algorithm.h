#pragma once

#include "graph.h"

void print_path(vector<vector<int>>& next, int u, int v, fstream& myfile);
vector<vector<int> > construct_next(vector<vector<int>> graph, int n);
void floydWarshall(const Graph& graph, int idx, fstream& myfile);
