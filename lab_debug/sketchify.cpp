#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
  PNG* image = new PNG(w, h);
  return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double hue) {
  HSLAPixel* p = new HSLAPixel(hue, 0.8, 0.5);
  return p;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    cout << "Reached line 23" << endl;
    original->readFromFile(inputFile);
    cout << "Reached line 25" << endl;
    unsigned width = original->width();
    unsigned height = original->height();
    cout << "width = " << width << " height = " << height << endl;
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(194);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
          // cout << "Reached line 39" << endl;
            // Calculate the pixel difference
            HSLAPixel& prev = original->getPixel(x - 1, y - 1);
            //cout << "Reached line 42" << endl;
            HSLAPixel& curr = original->getPixel(x, y);
            // cout << "Reached line 44" << endl;
            double diff = std::fabs(curr.h - prev.h);
            // cout << "Reached line 46" << endl;
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel& currOutPixel = (*output).getPixel(x, y);
            //cout << "Reached line 50" << endl;
            if (diff > 20) {
                currOutPixel = *myPixel;
          //cout << "Reached line 53" << endl;
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);
cout << "Reached line 60" << endl;
    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
