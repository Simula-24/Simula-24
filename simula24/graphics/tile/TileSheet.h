#ifndef CORE_GRAPHICS_TILE_TILE_SHEET_H_
#define CORE_GRAPHICS_TILE_TILE_SHEET_H_

#include <SDL.h>
#include <core/stl/array.h>
#include <core/types.h>
#include <cassert>
#include <core/stl/string.h>
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

    TileSheet(TileSheet&& other);
    TileSheet& operator=(TileSheet&& other);
    TileSheet(const TileSheet&);
    TileSheet& operator=(const TileSheet& other);
    ~TileSheet();

    FORCEINLINE const SDL_Rect& getTile(size_t id) const
    {
        assert(id < m_tiles.size());

        return m_tiles[id];
    }

    FORCEINLINE void addTile(const SDL_Rect& tileLoc) 
    {
        m_tiles.push_back(tileLoc);
    }
    
    inline void setTexture(SDL_Texture* texture)
    {
        if (!m_sheet) 
            m_sheet = texture;
    }
    FORCEINLINE SDL_Texture* getTexture()
    {
        return m_sheet;
    }

    FORCEINLINE size_t getNumTiles() const { return m_tiles.size(); }

    FORCEINLINE int getTileWidth() const { return m_tiles[0].w; }
    FORCEINLINE int getTileHeight() const { return m_tiles[0].h; }

    FORCEINLINE void setLocation(const stl::string& location) { m_location = location; }

    FORCEINLINE const stl::string& getLocation() const { return m_location; }
private:

    stl::array<SDL_Rect> m_tiles;
    
    SDL_Texture* m_sheet;
    stl::string m_location;
};

}

#endif // CORE_GRAPHICS_TILE_TILE_SHEET_H_