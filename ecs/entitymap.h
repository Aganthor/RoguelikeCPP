#pragma once

#include <array>
#include <map>
#include "Entity.h"

//
// It's effectivly a bidirectional map...
// Entity <-> ComponentInstance
//

namespace ecs {

const int MAX_NUMBER_OF_COMPONENTS = 1024;
using ComponentInstance = unsigned int;

struct EntityMap {
    Entity getEntity(ComponentInstance instance) { return instanceToEntity.at(instance); }

    ComponentInstance getInstance(Entity entity) { return entityToInstance.at(entity); }

    void add(Entity entity, ComponentInstance instance) {
        entityToInstance.insert({entity, instance});
        instanceToEntity.at(instance) = entity;
    }

    void update(Entity entity, ComponentInstance instance) {
        entityToInstance.at(entity) = instance;
        instanceToEntity.at(instance) = entity;
    }

    void remove(Entity entity) { entityToInstance.erase(entity); }

    std::map<Entity, ComponentInstance> entityToInstance;
    std::array<Entity, MAX_NUMBER_OF_COMPONENTS> instanceToEntity;
};

} //End of namespace ecs
