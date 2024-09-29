#ifndef GAME_TILE_TILE_SHEET_PARSER_H_
#define GAME_TILE_TILE_SHEET_PARSER_H_

#include "TileConfig.h"
#include <core/stl/string.h>
#include <core/stl/smart_ptr.h>

namespace simula24
{

class TileSheetParser
{
public:
    TileSheetParser();
    ~TileSheetParser();

    Status loadConfig(const stl::string& name);

    stl::shared_ptr<TileSheet> getNextSheet();

    bool good() const { return m_isGood; }

private:

    bool generateTileCoordinates(const TileSheetConfig& tsc);

    TileConfig m_tcfg;
    TileConfig::TileCfgIter m_cfgIter;
    TileConfig::TileCfgIter m_cfgIterEnd;

    bool m_isGood;
};

} // simula24


#endif // GAME_TILE_TILE_SHEET_PARSER_H_