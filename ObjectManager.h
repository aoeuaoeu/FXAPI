#ifndef __ObjectManager_H__
#define __ObjectManager_H__

#include <vector>


class Object;

class ObjectManager
{
public:
    void AddObject(Object *obj) { objects.push_back(obj); }
    std::vector<Object *> GetObjects() { return objects; }

private:
    std::vector<Object *> objects;
};


#endif