#include "SheetLoader.h"
#include "TileSheetDatabase.h"
#include "TileSheetParser.h"
#include <graphics/TextureManager.h>
#include <core/stl/string.h>

using simula24::SheetLoader;
using simula24::TileSheetParser;

bool SheetLoader::loadWorldTiles(const stl::string& cfgLoc)
{
    TileSheetParser tsp;
    
    if (tsp.loadConfig(cfgLoc) != OK)
        return false;

    m_activeList = &m_tdb.worldTiles;

    auto sheet = tsp.getNextSheet();
    while (sheet.has_value())
    {
        TileSheet& ts = sheet.value();
        stl::string location = "../data/tileset/cp437/";
        location += ts.getLocation();
        ts.setTexture(
            m_texmgr.loadFromFile(
                location
            )
        );
    
        m_activeList->push_back(std::move(ts));
        sheet = tsp.getNextSheet();
    }

    // no sheets parsed
    if (m_activeList->size() == 0)
        return false;

    return true;
}
