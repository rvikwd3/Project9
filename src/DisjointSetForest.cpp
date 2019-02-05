#include <algorithm>
#include <iostream>
#include "DisjointSetForest.h"

DisjointSetForest::DisjointSetForest() {

}

DisjointSetForest::DisjointSetForest( int no_of_elements ){
	init( no_of_elements );
}

DisjointSetForest::~DisjointSetForest() {

}

// Initialize the Union-Find forest
// -------------------------------------------------------------------------------- {{{
void DisjointSetForest::init( int no_of_elements ){
	this->elements.clear();
	this->elements.reserve( no_of_elements );
	this->num = no_of_elements;

	for (int i = 0; i < no_of_elements; i++ ){
		elements[i].rank	= 0;
		elements[i].size	= 1;
		elements[i].parent	= i;
	}
}
// -------------------------------------------------------------------------------- }}}

// Find the root of a Union-Find set
// -------------------------------------------------------------------------------- {{{
int DisjointSetForest::find( int x ){
	int y = x;

	while ( y != elements[y].parent )
		y = elements[y].parent;

	elements[x].parent = y;

	return y;
}
// -------------------------------------------------------------------------------- }}}

// Union of two sets
// -------------------------------------------------------------------------------- {{{
void DisjointSetForest::join( int x, int y ) {
	if ( elements[x].rank > elements[y].rank ) {
		elements[y].parent	= x;
		elements[x].size	+= elements[y].size;
	}
	else {
		elements[x].parent	= y;
		elements[y].size	+= elements[x].size;

		if ( elements[x].rank == elements[y].rank )
			elements[y].rank++;
	}

	num--;
	//fprintf(stdout, " [JOIN %d, %d]\tSets: %d", x, y, num);
}
// -------------------------------------------------------------------------------- }}}

// Returns size of set
int DisjointSetForest::size( int x ) {
	return elements[x].size;
}

// Returns number of sets
int DisjointSetForest::noOfElements() {
	return num;
}

// Segment the graph based on the weight of each edge
// -------------------------------------------------------------------------------- {{{
void DisjointSetForest::segmentGraph( int no_of_vertices, int no_of_edges, std::vector<Edge>& edges, double threshold ) {
	init(no_of_vertices);

	std::sort( edges.begin(), edges.end(), []( Edge& a, Edge& b){
			return a.weight < b.weight;
	});

	std::vector<double> threshold_array(no_of_vertices, threshold);

	for ( Edge& edge : edges ) {
		int a	= this->find( edge.node1 );
		int b	= this->find( edge.node2 );

		if ( a != b ) {

			fprintf(stdout, "[Edge N1 %d, N2 %d]\tWeight %lf\tThrsh A %lf\tThrsh B %lf", edge.node1, edge.node2, edge.weight, threshold_array[a], threshold_array[b]);

			// If the weight is below the threshold
			if ( edge.weight <= threshold_array[a] && edge.weight <= threshold_array[b] ) {

				this->join(a, b);
				fprintf(stdout, "\tJoin %d, %d", a, b);

				a = this->find( a );

				threshold_array[a] = edge.weight + threshold / this->size( a );
			}
			fprintf(stdout, "\n");
		}
	}
} // }}}
