#ifndef GRAPHICS_TILE_TILE_SHEET_DATABASE
#define GRAPHICS_TILE_TILE_SHEET_DATABSE

#include <core/stl/array.h>
#include "TileSheet.h"

namespace simula24
{

///
/// @brief
///     Game-specific Tile sheet lists
struct TileSheetDatabase
{
    TileSheetDatabase();
    ~TileSheetDatabase();

    stl::array<TileSheet> worldTiles;
    stl::array<TileSheet> creatureTiles;

};


}



#endif // GRAPHICS_TILE_TILE_SHEET_DATABASE