#include "ObjectTable.h"
#include <core/types.h>

using simula24::ObjectTable;
using simula24::U32;

int ObjectTable::insert(const stl::string& name, U32 tileID, bool isPassable)
{
    m_names.push_back(name);
    m_tileIDs.push_back(tileID);
    m_passableList.push_back(isPassable);
    return (int)(m_names.size()-1);
}

bool ObjectTable::isPassable(int id)
{
    return m_passableList[id];
}
U32 ObjectTable::getTileId(int id)
{
    return m_tileIDs[(size_t)id];
}
const stl::string&  ObjectTable::getName(int id)
{
    return m_names[id];
}

