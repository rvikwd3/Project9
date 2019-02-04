#include "segmentation.h"
#include "DisjointSetForest.h"
#include "convert.h"
#include <map>
#include <vector>
#include <iostream>
#include <math.h>

Segmentor::Segmentor() {
	std::cout << "Please provide an ImageMatrix to initialize the segmentor" << std::endl;

}

Segmentor::Segmentor(ImageMatrix& image){
	this->image			= image;
	this->image_size	= image.getDimensions();
}

Segmentor::~Segmentor() {

}

// Return number of sets in union-find
int Segmentor::noOfConnectedComponents(){
	return forest.noOfElements();
}

// L2 Norm difference between two color pixels
// -------------------------------------------------------------------------------- {{{
double Segmentor::diff( ImageMatrix& img, int x1, int x2, int y1, int y2 ) {
    std::vector<double> vec1;
    hsv temp_hsv = img.getHsvAt(x1, x2);
    vec1.push_back((double)(temp_hsv.h / 360.0)); 	// Divide by 360 because Hue is in terms of degrees.
    vec1.push_back(temp_hsv.s);
    vec1.push_back(temp_hsv.v);

    std::vector<double> vec2;
    temp_hsv = img.getHsvAt(y1, y2);
    vec2.push_back((double)(temp_hsv.h / 360.0));		// Divide by 360 because Hue is in terms of degrees.
    vec2.push_back(temp_hsv.s);
    vec2.push_back(temp_hsv.v);

    std::vector<double> difference;

    for( int i=0; i<3; i++) {
        difference.push_back(vec1[i] - vec2[i]);
    }

    double dot_result	= (pow(difference[0], 2) + pow(difference[1], 2) + pow(difference[2], 2)); 
    double norm2 		= sqrt( dot_result );
    //std::cout << "[Segmentor] Norm difference = " << norm2 << std::endl;

    return norm2;
}
// -------------------------------------------------------------------------------- }}}

// Apply union-find segmentation to the imagematrix
// -------------------------------------------------------------------------------- {{{
int Segmentor::applySegmentation(double threshold, int min_component_size){

	// Assuming that the image is already pre-processed: Gaussian blur
	int no_of_edges = 0;

	int width	= image_size[0];
	int height	= image_size[1];

	std::vector<Edge> edges( width * height * 4 );

	for (int y=0; y < height; y++ ) {
		for (int x=0; x < width; x++ ) {

			if ( x < width - 1 ) {
				edges[no_of_edges].node1	= y * width + x;
				edges[no_of_edges].node2	= y * width + (x + 1);
				edges[no_of_edges].weight	= diff (image, x, y, x+1, y);
				no_of_edges++;
			}

			if ( y < height - 1 ) {
				edges[no_of_edges].node1	= y			* width + x;
				edges[no_of_edges].node2	= (y + 1)	* width + x;
				edges[no_of_edges].weight	= diff (image, x, y, x, y+1);
				no_of_edges++;
			}

			if ( (x < width - 1) && (y < height - 1) ) {
				edges[no_of_edges].node1	= y			* width + x;
				edges[no_of_edges].node2	= (y + 1)	* width + (x + 1);
				edges[no_of_edges].weight	= diff (image, x, y, x+1, y+1);
			}

			if ( (x < width - 1) && (y > 0) ) {
				edges[no_of_edges].node1	= y			* width + x;
				edges[no_of_edges].node2	= (y - 1)	* width + (x + 1);
				edges[no_of_edges].weight	= diff (image, x, y, x+1, y-1);
				no_of_edges++;
			}
		}
	}

	// Resize the vector to number of edges, since we initialized it to way more than no_of_edges
	edges.resize( no_of_edges );

	// Apply segmentation to the edges
	forest.segmentGraph( height * width, no_of_edges, edges, threshold );
	
	// Union all the smaller sets
	for ( Edge& edge: edges ) {
		int a = forest.find( edge.node1 );
		int b = forest.find( edge.node2 );
		 
		if ( ( a != b ) \
			 && (  ( forest.size(a) < min_component_size ) \
				|| ( forest.size(b) < min_component_size )
				)
		   ) {
			
			//fprintf(stderr, "\n[MIN COMP] %d, %d\n", a, b);
			forest.join(a, b);
		}
	}

	return noOfConnectedComponents();
}
// -------------------------------------------------------------------------------- }}}

