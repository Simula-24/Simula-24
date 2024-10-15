#include "ObjectTable.h"
#include <core/types.h>

using simula24::ObjectTable;
using simula24::U32;

int ObjectTable::insert(const stl::string& name, U32 tileID, bool isPassable, TileSize size)
{
    m_names.push_back(name);
    m_tileIDs.push_back(tileID);
    m_passableList.push_back(isPassable);
    m_tileSizes.push_back(size);
    return (int)(m_names.size()-1);
}

