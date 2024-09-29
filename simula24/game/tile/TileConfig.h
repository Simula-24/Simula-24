#ifndef CORE_GAME_TILE_TILE_SHEET_PARSER_H_
#define CORE_GAME_TILE_TILE_SHEET_PARSER_H_

#include <core/stl/string.h>
#include <core/stl/array.h>
#include <core/stl/smart_ptr.h>
#include <core/types.h>
#include <core/io/File.h>
#include <SDL.h>

#include <game/tile/TileSheet.h>

namespace simula24
{

/// @brief Represents data found in tileset.inf
struct TileSheetConfig
{
    stl::string filename;
    int imageHeight;
    int imageWidth;
    int tileHeight;
    int tileWidth;
};

///
/// @brief
///     Handles parsing of a tile sheet + its config
///
/// NOTE: we might need a texture manager class 
///       due to how SDL_Renderer is shared/used
/// 
class TileConfig
{
public:

    using TileCfgIter =  stl::array<TileSheetConfig>::iterator;
    using CTileCfgIter = stl::array<TileSheetConfig>::const_iterator;

    TileConfig();
    ~TileConfig();

    /// Load and parse a config file
    Status load(const stl::string& configFileName);

    TileCfgIter getConfigIterBegin() { return m_sheetConfigs.begin(); }
    TileCfgIter getConfigIterEnd() { return m_sheetConfigs.end(); }

    CTileCfgIter getCConfigIterBegin() const { return m_sheetConfigs.cbegin(); }
    CTileCfgIter getCConfigIterEnd() const { return m_sheetConfigs.cend(); }


private:
    /// Extract the width and height using this format: <h>x<w> or <h>X<w>
    bool extractDimensions(const stl::string& source, int& w_out, int& h_out);

    /// Parse the configuration file
    bool parseConfig(const stl::string& cfg);

    stl::array<TileSheetConfig> m_sheetConfigs;
};

}

#endif // CORE_GAME_TILE_TILE_SHEET_PARSER_H_