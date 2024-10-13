#ifndef GRAPHICS_TILE_TILE_SHEET_PARSER_H_
#define GRAPHICS_TILE_TILE_SHEET_PARSER_H_

#include "TileConfig.h"
#include <core/stl/string.h>
#include <core/stl/smart_ptr.h>
#include <optional>
namespace simula24
{

class TileSheetParser
{
public:
    TileSheetParser();
    ~TileSheetParser();

    Status loadConfig(const stl::string& name);

    std::optional<TileSheet> getNextSheet();

    bool good() const { return m_isGood; }

private:

    bool generateTileCoordinates(const TileSheetConfig& tsc, TileSheet& dest);

    TileConfig m_tcfg;
    TileConfig::TileCfgIter m_cfgIter;
    TileConfig::TileCfgIter m_cfgIterEnd;

    bool m_isGood;
};

} // simula24


#endif // GRAPHICS_TILE_TILE_SHEET_PARSER_H_