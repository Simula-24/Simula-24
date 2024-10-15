#ifndef GRAPHICS_TILE_TILE_SHEET_DATABASE
#define GRAPHICS_TILE_TILE_SHEET_DATABASE

#include <core/stl/array.h>
#include "TileSheet.h"

namespace simula24
{

using TileSheetList = stl::array<TileSheet>;

///
/// @brief
///     Game-specific Tile sheet lists
struct TileSheetDatabase
{
    TileSheetDatabase();
    ~TileSheetDatabase();

    TileSheetList worldTiles;
    TileSheetList creatureTiles;

};


}



#endif // GRAPHICS_TILE_TILE_SHEET_DATABASE