#ifndef APP_OBJECT_OBJECT_TABLE_H_
#define APP_OBJECT_OBJECT_TABLE_H_

#include <core/stl/string.h>
#include <core/stl/array.h>
#include <core/types.h>
#include <graphics/tile/TileSize.h>
#include <core/types.h>
namespace simula24
{

class ObjectTable
{
public:
    
    int insert(const stl::string& name, U32 tileID, bool isPassable, TileSize size);

    FORCEINLINE bool isPassable(int id) const { return m_passableList[id]; }
    
    FORCEINLINE U32 getTileId(int id) const { return m_tileIDs[(size_t)id]; }
    
    FORCEINLINE const stl::string& getName(int id) const { return m_names[id]; }

    FORCEINLINE TileSize getTileSize(int id) const { return m_tileSizes[(size_t)id]; }
private:
    stl::array<bool> m_passableList;
    stl::array<stl::string> m_names;
    stl::array<U32> m_tileIDs;
    stl::array<TileSize> m_tileSizes;
};

}


#endif // GAME_OBJECT_OBJECT_TABLE_H_