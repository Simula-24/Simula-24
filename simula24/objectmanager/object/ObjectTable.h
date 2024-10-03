#ifndef APP_OBJECT_OBJECT_TABLE_H_
#define APP_OBJECT_OBJECT_TABLE_H_

#include <core/stl/string.h>
#include <core/stl/array.h>
#include <core/types.h>

namespace simula24
{

class ObjectTable
{
public:
    
    int insert(const stl::string& name, U32 tileID, bool isPassable);

    bool isPassable(int id);
    U32 getTileId(int id);
    const stl::string& getName(int id);




private:
    stl::array<bool> m_passableList;
    stl::array<stl::string> m_names;
    stl::array<U32> m_tileIDs;
};

}


#endif // GAME_OBJECT_OBJECT_TABLE_H_