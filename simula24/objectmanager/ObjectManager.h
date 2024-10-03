#ifndef OBJECT_MANAGER_OBJECT_MANAGER_H_
#define OBJECT_MANAGER_OBJECT_MANAGER_H_

namespace simula24
{

class ObjectManager
{
public:

    static ObjectManager& get() { return s_instance; }

    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;
private:
    ObjectManager() {}
    static ObjectManager s_instance;
};


} // simula24

#endif // OBJECT_MANAGER_OBJECT_MANAGER_H_