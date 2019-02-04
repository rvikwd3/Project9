/*	Effificient Graph Based Image Segmentor by Saburo Okita
 *
 *	ImageMatrix Implementation
 *
 *	Segments image into connected color components using a Union-Find disjoint data structure:
 *		Union-Find can be found here: https://www.hackerearth.com/practice/notes/disjoint-set-union-union-find/
 *		1.	Convert the image into a graph with
 *				each pixel as a Node
 *				each edge is the L2 norm difference between HSV pixels
 *		2.	Create sets by joining (Union) pixels with a low enough L2 difference
 *		3.	Glob the really small sets together
 *		4.	Return the number of sets
 *			OR
 *		4.	Return a recolored image with each set the average color of the pixels
*/

#ifndef SEGMENTATION_H
#define SEGMENTATION_H

#include <vector>

#include "DisjointSetForest.h"
#include "imagematrix.h"

class Segmentor {
public:
    Segmentor();
	Segmentor(ImageMatrix& image);
    ~Segmentor();

    double diff ( ImageMatrix& img, int x1, int x2, int y1, int y2 );

    int 		applySegmentation(double threshold, int min_component_size);
    //ImageMatrix	recolor( bool random_color = false );
    int 		noOfConnectedComponents();

protected:
    ImageMatrix 		image;
	std::array<int, 2>	image_size;
	DisjointSetForest	forest;

};

#endif
