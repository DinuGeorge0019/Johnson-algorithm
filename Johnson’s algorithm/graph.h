#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>

using namespace std;

struct  Edge
{
	int src;
	int dest;
	int weight;
};

class Graph
{
public:
	int n;
	vector<vector<int>> adj_matrix;
	vector<Edge> edges;
	Graph(vector<Edge>& edges, int n);
};

void print_graph(Graph& graph);
void write_random_graph(fstream& myfile);
