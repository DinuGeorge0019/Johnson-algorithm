#include "Johnson's_algorithm.h"


void print_path(vector<int>& parent, int dest, fstream& myfile, vector<vector<pair<int, int>>> old_graph)
{
	vector<int> path;

	int i = dest;
	while (i != -1)
	{
		path.push_back(i);
		i = parent[i];
	}
	reverse(path.begin(), path.end());


	for (int j = 0; j < (int)path.size() - 1; j++)
	{
		myfile << path[j] << "->";
	}
	myfile << path[path.size() - 1] << " ";

	int weight = 0;
	for (int j = 0; j < (int)path.size() - 1; j++)
	{
		for (auto& dest : old_graph[path[j]])
		{
			if (dest.first == path[j + 1])
			{
				weight += dest.second;
			}
		}
	}

	myfile << " w : " << weight;
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

	for (int i = 0; i < n; i++)
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

void Dijkstra(vector<vector<pair<int, int>>> adj_list, int src, fstream& myfile, vector<vector<pair<int, int>>> old_graph, chrono::high_resolution_clock::time_point& start_point, chrono::high_resolution_clock::time_point& end_point)
{
	start_point = std::chrono::high_resolution_clock::now();

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

	end_point = std::chrono::high_resolution_clock::now();

	myfile << "Source : " << src << endl;
	for (int i = 0; i < n; i++)
	{
		if (dist[i] == INT_MAX) continue;
		myfile << src << " <-> " << i << "  path : ";
		print_path(parent, i, myfile, old_graph);
		myfile << endl;
	}
	myfile << endl;



}

void Johnson_algorithm(const Graph& graph, int idx, fstream& myfile)
{

	myfile.open("output_Johnson.txt", ios::out | ios::app);
	myfile << "< - - - - - - GRAPH " << idx << " - - - - - - > " << endl;


	std::chrono::high_resolution_clock::time_point start_point = std::chrono::high_resolution_clock::now();

	vector<int> modify_weights = Bellman_Ford(graph.edges, graph.n);

	if (modify_weights.empty())
	{

		std::chrono::high_resolution_clock::time_point end_point = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time_span = end_point - start_point;
		std::cout << "Johnson's algorithm time : " << time_span.count() << " milliseconds.";
		std::cout << std::endl;

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

	std::chrono::high_resolution_clock::time_point end_point = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> time_span = end_point - start_point;

	for (int i = 0; i < graph.n; i++)
	{
		std::chrono::high_resolution_clock::time_point start_temp;
		std::chrono::high_resolution_clock::time_point end_temp;

		Dijkstra(modified_graph, i, myfile, graph.adj_list, start_temp, end_temp);

		std::chrono::duration<double, std::milli> time_span_temp = end_temp - start_temp;

		time_span += time_span_temp;
	}

	std::cout << "Johnson's algorithm time : " << time_span.count() << " milliseconds.";
	std::cout << std::endl;


	myfile.close();
}