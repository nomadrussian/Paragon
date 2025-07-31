#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

typedef unsigned long long EntityID;

class EntityManager
{
private:
    EntityID nextEntityID = 0;
public:
    EntityManager();
    void createNewEntity();
    void removeAllEntities();
};

#endif // ENTITYMANAGER_HPP
