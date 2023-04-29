#pragma once
#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "DynamicArray.h"

int node_ammount = 0;

struct Node
{
	double x, y;
};

struct Edge
{
	size_t i, j;
	double cost;

	bool operator < (const Edge& other)
	{
		if (cost < other.cost) return true;
		else return false;
	}

	bool operator > (const Edge& other)
	{
		if (cost > other.cost) return true;
		else return false;
	}

	bool operator >= (const Edge& other)
	{
		if (cost >= other.cost) return true;
		else return false;
	}
};

struct Graph
{
	DynamicArray<Node> nodes;
	DynamicArray<Edge> edges;

	Graph(std::string path)
	{
		std::ifstream file(path);

		if (file.is_open())
		{
			Node node;
			size_t n;
			file >> n;
			node_ammount = n;
			for (size_t i = 0; i < n; i++)
			{
				file >> node.x >> node.y;
				nodes.add(node);
			}

			Edge edge;
			size_t e;
			file >> e;
			for (size_t i = 0; i < e; i++)
			{
				file >> edge.i >> edge.j >> edge.cost;
				edges.add(edge);
			}
		}
		else
		{
			std::cout << "Error: Could not open file" << std::endl;
			exit(1);
		}

	}
};

class UnionFind
{
private:
	int* parents;
	int* ranks;
public:
	UnionFind(size_t n) : parents(new int[n]), ranks(new int[n]) 
	{
		for (size_t i = 0; i < n; i++)
		{
			parents[i] = i;
			ranks[i] = 1;
		}
	}

	int find(int x)
	{
		// Find the root of given node
		int root = x;
		while (root != parents[root]) root = parents[root];

		// Path Compression
		while (x != root)
		{
			int next = parents[x];
			parents[x] = root;
			x = next;
		}

		return root;
	}

	void unify(int i, int j)
	{
		int root_i = find(i);
		int root_j = find(j);

		//std::cout << "Dla i = " << i << ", j = " << j << "\n";
		//std::cout << "root_i: " << root_i << "\t" << "root_j: " << root_j << " ranks[root_i]:" << ranks[find(i)] << " ranks[root_j]:" << ranks[find(j)] << "\n";;
		if (root_i != root_j)
		{
			if (ranks[root_i] < ranks[root_j])
			{
				//std::cout << "1) UNIFY " << i << "->" << j << "\n";
				parents[root_i] = root_j;
				ranks[root_j] += ranks[root_i];
				ranks[root_i] = 0;
			}
			else
			{
				//std::cout << "2) UNIFY " << j << "->" << i << "\n";
				parents[root_j] = root_i;
				ranks[root_i] += ranks[root_j];
				ranks[root_j] = 0;
			}
		}
		/*std::cout << "root_i: " << find(i) << "\t" << "root_j: " << find(j) << " ranks[root_i]:" << ranks[root_i] << " ranks[root_j]:" << ranks[root_j] << "\n";
		std::cout << "PARENTS: " << "\n"; for (int i = 0; i < node_ammount; i++) { std::cout << " " << parents[i] << " "; } std::cout << "\n";  for (int i = 0; i < node_ammount; i++) { std::cout << "[" << i << "]"; } std::cout << "\n";
		std::cout << "RANKS: " << "\n"; for (int i = 0; i < node_ammount; i++) { if(i<10) std::cout << " " << ranks[i] << " "; else std::cout << "  " << ranks[i] << " "; } std::cout << "\n";  for (int i = 0; i < node_ammount; i++) { std::cout << "[" << i << "]"; } std::cout << "\n";
		std::cout << "----------------------------------------------------------------------------------------------------------" << "\n";*/
	}
};

