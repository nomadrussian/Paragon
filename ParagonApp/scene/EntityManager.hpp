#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>

typedef unsigned long long EntityID;

class EntityManager
{
private:
    EntityID nextEntityID = 0;
    std::vector<EntityID> entityList;

public:
    EntityManager();
    EntityID createNewEntity();
    void removeEntity(EntityID entity);
    void removeAllEntities();
    bool entityExists(EntityID entity);
};

#endif // ENTITYMANAGER_HPP
