#ifndef OBJECT_MANAGER_OBJECT_MANAGER_H_
#define OBJECT_MANAGER_OBJECT_MANAGER_H_

#include "ObjectTable.h"

namespace simula24
{

///
/// @brief
///     Manages our data tables
/// 
///     Specifically manages 
///         - Tile IDs
///         - Creature IDs
///         - Object IDs
///         - Item IDs
///         - Material IDs
/// 
class ObjectManager
{

public:

    constexpr static ObjectTable& getObjectTable() { return get().m_objectTable; }

private:

    ObjectTable m_objectTable;

public:
    static constexpr ObjectManager& get() { return s_instance; }

    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
private:
    ObjectManager() {}
    static ObjectManager s_instance;
};


} // simula24

using OM/*NOMNOM*/ = simula24::ObjectManager;

#endif // OBJECT_MANAGER_OBJECT_MANAGER_H_