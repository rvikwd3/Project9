#ifndef DISJOINTSETFOREST_H
#define DISJOINTSETFOREST_H

#include <vector>

// Disjointed Set Forest node
struct SetNode{
	int rank;
	int parent;
	int size;

};

// Edge between the nodes
struct Edge {
	int node1;
	int node2;
	double weight;

	bool operator<( const Edge& other) {
		return weight < other.weight;
	}
};

// Union-find disjoint set
class DisjointSetForest{
	public:
		DisjointSetForest();
		DisjointSetForest( int no_of_elements );
		~DisjointSetForest();

		void segmentGraph( int no_of_vertices, int no_of_edges, std::vector<Edge>& edges, double threshold );

		int noOfElements();
		int size( int x );
		void join( int x, int y );
		int find( int x );
		void init( int no_of_elements );

	private:
		std::vector<SetNode> elements;
		int num;
};

#endif
