#ifndef GRAPHICS_TILE_SHEET_LOADER_H_
#define GRAPHICS_TILE_SHEET_LOADER_H_

#include <core/stl/string.h>
#include "TileSheetDatabase.h"
namespace simula24
{

class TextureManager;
///
/// @brief
///     Loads tilesheets
/// 
class SheetLoader
{
public:

    SheetLoader(TileSheetDatabase& db, TextureManager& mgr) 
        : m_tdb(db), m_activeList(nullptr), m_texmgr(mgr) {}

    bool loadWorldTiles(const stl::string& cfgLoc);

private:

    /// Target Database, where we are sourcing lists
    TileSheetDatabase& m_tdb;

    /// where we are currently storing sheets
    TileSheetList* m_activeList;

    /// used to load images
    TextureManager& m_texmgr;
};

}

#endif // GRAPHICS_TILE_SHEET_LOADER_H_