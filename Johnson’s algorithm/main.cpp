#include "Johnson's_algorithm.h"

int main()
{

	fstream output_file;
	fstream input_file;

	while (1)
	{

		for (int i = 0; i < 20; i++)
			cout << "- - -";
		cout << endl;

		cout << "Options : " << endl;
		cout << "1. Generate ten new random directed graphs " << endl;
		cout << "2. Find all-pairs shortest paths using Johnson's algorithm" << endl;
		cout << "3. Find all-pairs shortest paths using Johnson's algorithm for a user defined graph" << endl;
		cout << "4. Exit" << endl;


		int option;
		cin >> option;

		switch (option)
		{

		case 1:
		{
			write_random_graph(output_file);
			break;
		}

		case 2:
		{
			//delete everything from output file
			output_file.open("output.txt", ios::trunc | ios::out);
			output_file.close();

			input_file.open("input.txt", ios::in);


			for (int i = 0; i < 10; i++)
			{
				
				vector<Edge> edges;
				int N, E;

				input_file >> N >> E;

				for (int i = 0; i < E; i++)
				{
					Edge e;
					input_file >> e.src;
					input_file >> e.dest;
					input_file >> e.weight;
					edges.push_back(e);
				}

				Graph new_graph(edges, N);

				Johnson_algorithm(new_graph, i,  output_file);
			}

			input_file.close();
			

			break;
		}

		case 3:
		{
			output_file.open("output.txt", ios::trunc | ios::out);
			output_file.close();
			
			vector<Edge> edges;
			int N, E;
			cout << "Number of vertices in graph :" << endl;
			cin >> N;
			cout << "Number of edges in graph : maxim V*(V-1)" << endl;
			cin >> E;

			cout << "Enter the edges : (u, v, w)" << endl;
			for (int i = 0; i < E; i++)
			{
				Edge e;
				cin >> e.src;
				cin >> e.dest;
				cin >> e.weight;
				edges.push_back(e);
			}

			Graph new_graph(edges, N);

			cout << "User's graph : " << endl;
			print_graph(new_graph);

			Johnson_algorithm(new_graph, 0, output_file);

			break;
		}

		case 4:
		{
			return 0;
		}
			

		default:
			break;

		}
	}


}

