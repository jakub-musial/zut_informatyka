#include "UnionFind.h"
#include "BinaryHeap.h"

DynamicArray<Edge> kruskal(Graph graph)
{
	//graph.edges.insertion_sort();
	BinaryHeap<Edge> bh_sort(&(graph.edges), true); bh_sort.sort();
	
	DynamicArray<Edge> mst;
	UnionFind uf(graph.edges.get_size());
	for (size_t it = 0; it < graph.edges.get_size(); it++)
	{

		int i_group = uf.find(graph.edges[it].i);
		int j_group = uf.find(graph.edges[it].j);

		if (i_group != j_group)
		{
			uf.unify(i_group, j_group);
			mst.add(graph.edges[it]);
		}
	}
	return mst;
}

void display_mts(DynamicArray<Edge>* mst)
{
	std::cout << "MST" << std::endl;
	std::cout << "Size: " << mst->get_size() << std::endl;
	double cost = 0;
	for (int it = 0; it < mst->get_size(); it++)
	{
		std::cout << mst->operator[](it).i << "\t" << mst->operator[](it).j << "\t" << "\t" << mst->operator[](it).cost << std::endl;
		cost += mst->operator[](it).cost;
	}
	std::cout << "Cost: " << cost;
}

int main()
{
	Graph graph("g1.txt");
	DynamicArray<Edge> mst = kruskal(graph);
	display_mts(&mst);
}

