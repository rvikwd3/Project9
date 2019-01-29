#include <iostream>
#include "imagematrix.h"
#include "magick.h"

// --------------------------------------------------------------------------------
ImageMatrix::ImageMatrix() { // {{{
    std::cout << "[IMAGE MATRIX] Please specify the image size to ImageMatrix" << std::endl;
    // Initialize RGB and HSV matrices
} // }}}

// --------------------------------------------------------------------------------
ImageMatrix::ImageMatrix(const Magick::Image& image) { // {{{
    // Get image dimensions
    std::vector<int> dims = getImageDimensions(image);

    // Initialize RGB & HSV matrices to dimension size
    rgb_matrix.resize(boost::extents[ dims[0] ][ dims[1] ]);
    hsv_matrix.resize(boost::extents[ dims[0] ][ dims[1] ]);

    // Copy RGB data to RGB matrix
    for ( size_t i = 0; i < rgb_matrix.shape()[0]; i++) {
        for (size_t j = 0; j < rgb_matrix.shape()[1]; j++) {

            rgb_matrix[i][j].r	= (double)( image.pixelColor(j,i).quantumRed() / 65535.0 );
            rgb_matrix[i][j].g	= (double)( image.pixelColor(j,i).quantumGreen() / 65535.0 );
            rgb_matrix[i][j].b	= (double)( image.pixelColor(j,i).quantumBlue() / 65535.0 );


            // Convert RGB data to HSV matrix
            // 		Cons:
            // 			Overhead of converting RGB to HSV every time a new image is created.
            // 			Do we always use the HSV matrix? If not, then converting RGB->HSV is an overhead.
            hsv_matrix[i][j]	= Convert::rgb2hsv(rgb_matrix[i][j]);

            //printf("[IMAGEMATRIX CNSTRCT RGB] (%d, %d)\tR: %9.0f\tG: %9.0f\tB: %9.0f\n", i, j, rgb_matrix[i][j].r, rgb_matrix[i][j].g, rgb_matrix[i][j].b);

            //printf("[IMAGEMATRIX CNSTRCT HSV] (%d, %d)\tH: %9.0f\tS: %9.0f\tV: %9.0f\n", i, j, hsv_matrix[i][j].h, hsv_matrix[i][j].s, hsv_matrix[i][j].v);
        }
    }

} // }}}

// --------------------------------------------------------------------------------
std::array<int, 2> ImageMatrix::getDimensions() { // {{{
    // return matrix size
    std::array<int, 2> rgb_size = { (int)(rgb_matrix.shape()[0]), (int)(rgb_matrix.shape()[1]) };
    std::array<int, 2> hsv_size = { (int)(hsv_matrix.shape()[0]), (int)(hsv_matrix.shape()[1]) };

    std::array<int, 2> retval;

    if ( ( rgb_size[0] != hsv_size[0] ) || ( rgb_size[1] != hsv_size[1] ) ) {
        std::cerr << "[ERROR] RGB and HSV matrix sizes don't match" << std::endl;

        retval = {{ -1, -1 }};
    } else {
        std::cout << "[IMGMATRIX getDimensions()] RGB & HSV Matrices match sizes" << std::endl;

        retval = {{ (int)rgb_matrix[0].size(), (int)rgb_matrix[1].size() }};
    }

    return retval;
} // }}}

// --------------------------------------------------------------------------------
rgb ImageMatrix::getRgbAt(unsigned row, unsigned col) { // {{{
    // return this(row, col);
    rgb retval;

    std::array<int, 2> matrix_size = this->getDimensions();

    // Return {-1, -1, -1} if (row, col) tries to access outside the imagematrix
    if ( (row >= matrix_size[0]) || (col >= matrix_size[1]) ) {
        fprintf(stderr, "[ERROR] getRgbAt(%d, %d) is trying to access elements outside of the image matrix", row, col);
        return retval;
    }

    // get rgb values from imagematrix
    retval.r = rgb_matrix[row][col].r;
    retval.g = rgb_matrix[row][col].g;
    retval.b = rgb_matrix[row][col].b;

    printf("[getRgbAt(%d, %d)] \tRows: %d\tCols: %d\n", row, col, matrix_size[0], matrix_size[1]);
    printf("[getRgbAt(%d, %d)] \tR: %9.2f\tG: %9.2f\tB: %9.2f\n", row, col, retval.r, retval.g, retval.b);

    return retval;
} // }}}

// --------------------------------------------------------------------------------
hsv ImageMatrix::getHsvAt(unsigned row, unsigned col) { // {{{
    // return this(row, col);
    hsv retval;

    std::array<int, 2> matrix_size = this->getDimensions();

    // ensure row, col are within matrix size
    if ( (row >= matrix_size[0]) || (col >= matrix_size[1]) ) {
        fprintf(stderr, "[ERROR] getRgbAt(%d, %d) is trying to access elements outside of the image matrix", row, col);
        return retval;
    }

    // get hsv values from imagematrix
    retval.h = hsv_matrix[row][col].h;
    retval.s = hsv_matrix[row][col].s;
    retval.v = hsv_matrix[row][col].v;

    printf("[getHsvAt(%d, %d)] \tRows: %d\tCols: %d\n", row, col, matrix_size[0], matrix_size[1]);
    printf("[getHsvAt(%d, %d)] \tH: %9.2f\tS: %9.2f\tV: %9.2f\n", row, col, retval.h, retval.s, retval.v);

    return retval;
} // }}}
