#include "Johnson's_algorithm.h"


void print_path(vector<int> parent, int dest, fstream& myfile)
{
	vector<int> path;

	int i = dest;
	while (i != -1)
	{
		path.push_back(i);
		i = parent[i];
	}
	reverse(path.begin(), path.end());


	for (int i = 0; i < (int)path.size() - 1; i++)
	{
		myfile << path[i] << "->";
	}
	myfile << path[path.size() - 1];

}


vector<int> Bellman_Ford(vector<Edge> edges, int n)
{

	vector<int> dist(n + 1, INT_MAX);
	dist[n] = 0;

	for (int i = 0; i < n; i++)
	{
		Edge new_edge;
		new_edge.src = n;
		new_edge.dest = i;
		new_edge.weight = 0;
		edges.push_back(new_edge);
	}

	for (int i = 0; i < n - 1; i++)
	{
		bool flag = false;
		for (auto& edge : edges)
		{
			int u = edge.src;
			int v = edge.dest;
			int weight = edge.weight;
			if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				flag = true;
			}
		}
		if (flag == false)
		{
			break;
		}

	}

	for (auto& edge : edges)
	{
		int u = edge.src;
		int v = edge.dest;
		int weight = edge.weight;
		if (dist[u] != INT_MAX && dist[v] > dist[u] + weight)
		{
			return {}; // If negative cycle is detected, simply return 
		}
	}


	vector<int> res(dist.begin(), dist.end() - 1);

	return res;

}

void Dijkstra(vector<vector<pair<int, int>>> adj_list, int src, fstream& myfile)
{
	int n = adj_list.size();

	vector<int> parent(n);
	parent[src] = -1;

	vector<int> dist(n, INT_MAX);
	dist[src] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push(make_pair(0, src));

	while (!Q.empty())
	{
		pair<int, int> node = Q.top();
		Q.pop();

		if (node.first > dist[node.second])
			continue;

		for (auto i : adj_list[node.second])
		{
			int u = node.second;
			int v = i.first;
			int w = i.second;
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				Q.push(make_pair(dist[v], v));
				parent[v] = u;
			}
		}
	}


	myfile << "Source : " << src << endl;
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == INT_MAX) continue;
		myfile << src << " <-> " << i << " w : " << dist[i] << "  path : ";
		print_path(parent, i, myfile);
		myfile << endl;
	}
	myfile << endl;



}

void Johnson_algorithm(Graph graph, int idx, fstream& myfile)
{

	myfile.open("output.txt", ios::out | ios::app);
	myfile << "< - - - - - - GRAPH " << idx << " - - - - - - > " << endl;


	vector<int> modify_weights = Bellman_Ford(graph.edges, graph.n);

	if (modify_weights.empty())
	{
		myfile << "Graph contains negative weight cycle" << endl;
		myfile.close();
		return;
	}


	vector<vector<pair<int, int>>> modified_graph = graph.adj_list;

	for (int src = 0; src < graph.n; src++)
	{
		for (auto& dest : modified_graph[src])
		{
			dest.second = dest.second + modify_weights[src] - modify_weights[dest.first];
		}
	}


	for (int i = 0; i < graph.n; i++)
	{
		Dijkstra(modified_graph, i, myfile);
	}


	myfile.close();
}