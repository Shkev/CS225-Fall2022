/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(const LUVAPixel& pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}


MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    map<Point<3>, TileImage*> avg_color_tile_map;
    vector<Point<3>> avg_tile_colors;
    for (TileImage& img : theTiles) {
        Point<3> avg_color_pt = convertToXYZ(img.getAverageColor());
        avg_tile_colors.push_back(avg_color_pt);
        avg_color_tile_map.insert(make_pair(avg_color_pt, &img));
    }

    KDTree<3> avg_colors_kdt(avg_tile_colors);

    // go through all regions and determine tile to use
    for (int r = 0; r < theSource.getRows(); ++r) {
        for (int c = 0; c < theSource.getColumns(); ++c) {
            Point<3> source_region_avg_clr = convertToXYZ(theSource.getRegionColor(r, c));
            Point<3> nearest_tile_avg_clr = avg_colors_kdt.findNearestNeighbor(source_region_avg_clr);
            TileImage* nearest_tile = avg_color_tile_map.at(nearest_tile_avg_clr);
            mosaic->setTile(r, c, nearest_tile);
        }
    }

    return mosaic;
}

