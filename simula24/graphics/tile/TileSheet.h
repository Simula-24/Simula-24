#ifndef CORE_GRAPHICS_TILE_TILE_SHEET_H_
#define CORE_GRAPHICS_TILE_TILE_SHEET_H_

#include <SDL.h>
#include <core/stl/array.h>

namespace simula24
{

///
/// @brief
///     Represents a single tilesheet
///     
///     This class holds an array of rectangles,
///     each referencing a part of the tilesheet
/// 
class TileSheet
{
public:
    TileSheet();
    ~TileSheet();

    const SDL_Rect& getTile(size_t id) const;

    void addTile(const SDL_Rect& tileLoc);
    void setTexture(SDL_Texture* texture)
    {
        if (!m_sheet) 
            m_sheet = texture;
    }

    size_t getNumTiles() { return m_tiles.size(); }
    int getTileWidth() { return m_tiles[0].w; }
    int getTileHeight() { return m_tiles[0].h; }
private:

    stl::array<SDL_Rect> m_tiles;
    
    SDL_Texture* m_sheet;

};

}

#endif // CORE_GRAPHICS_TILE_TILE_SHEET_H_