#include "graph.h"

Graph ::Graph(vector<Edge>& edges, int n) {

	adj_list.resize(n);
	this->n = n;
	this->edges = edges;

	for (auto& edge : edges)
	{
		adj_list[edge.src].push_back(make_pair(edge.dest, edge.weight));

		//uncomment if you need undirected graph
		//adj_list[edge.dest].push_back(make_pair(edge.src, edge.weight));
	}
}

void print_graph(Graph& graph)
{
	for (int src = 0; src < graph.n; src++)
	{
		cout << src << " -> ";
		for (auto& dest : graph.adj_list[src])
		{
			cout << dest.first << " w:" << dest.second << ",  ";
		}
		cout << endl;
	}
}



void write_random_graph(fstream& myfile)
{
	myfile.open("input.txt", ios::out | ios::trunc);

	// Define the maximum number of vertices of the graph 
	int MAX_VERTICES = 15;

	// Define the maximum number of edges 
	int MAX_EDGES = 200;

	// Define the maximum weight of edges 
	int MAXWEIGHT = 150;

	//Define the number of generated graphs
	int RUN = 10;

	// For random values every time 
	srand((unsigned)time(NULL));

	for (int i = 0; i < RUN; i++)
	{

		int N;    // Number of Vertices 
		int E; // Number of Edges 

		N = 5 + rand() % (MAX_VERTICES - 5 + 1);

		E = 4 + rand() % (MAX_EDGES - 4 + 1);

		while (E > N * (N - 1)/2)               // we are asking for a sparse  graph
			E = 4 + rand() % (MAX_EDGES - 4 + 1);



		myfile << N << " " << E << endl;

		set<pair<int, int>> container;

		for (int j = 1; j <= E; j++)
		{
			int u = rand() % N;
			int v = rand() % N;
			pair<int, int> edge = make_pair(u, v);
			pair<int, int> reverse_edge = make_pair(v, u);


			// Search for a new edge (a, b) such that there is not edge (b, a) in the container 
			while (container.find(edge) != container.end() ||
				container.find(reverse_edge) != container.end())
			{
				u = rand() % N;
				v = rand() % N;
				edge = make_pair(u, v);
				reverse_edge = make_pair(v, u);
			}
			container.insert(edge);
		}

		for (auto it = container.begin(); it != container.end(); ++it)
		{
			int wt = -30 + rand() % MAXWEIGHT;
			myfile << it->first << " " << it->second << " " << wt << endl;
		}

		myfile << endl;
	}

	myfile.close();

}
