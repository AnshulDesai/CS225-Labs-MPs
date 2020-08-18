/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;

/**
* Takes in a pixel and returns a Point with the constraints of L-U-V (x, y, z).
**/
Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

/**
* Function that takes a SourceImage and a vector of TileImages
* and returns a MosaicCanvas pointer. It maps the rectangular regions of the
* SourceImage to TileImages.
**/
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     vector<Point<3>> vectPoint;
     vector<TileImage>::iterator it;
     MosaicCanvas * mCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

     for (it = theTiles.begin(); it != theTiles.end(); it++) {
       Point<3> xyzPoint (convertToXYZ((*it).getAverageColor()));
       vectPoint.push_back(xyzPoint);
     }

     KDTree<3> tempTree (vectPoint);

     for (int x = 0; x < theSource.getRows(); x++) {
       for (int y = 0; y < theSource.getColumns(); y++) {
         int indexTile = 0;

         Point<3> pointToNN (convertToXYZ(theSource.getRegionColor(x, y)));
         Point<3> pointNN = tempTree.findNearestNeighbor(pointToNN);

         for (int i = 0; vectPoint[i] != pointNN; i++) {
           indexTile = i;
         }

         indexTile++;

         TileImage & imgTile = theTiles[indexTile];
         mCanvas->setTile(x, y, &imgTile);
       }
     }
     return mCanvas;
}
