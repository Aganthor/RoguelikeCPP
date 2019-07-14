#include "entitymanager.h"

namespace ecs {

Entity EntityManager::createEntity() {
    lastEntity++;
    return {lastEntity};
}

void EntityManager::destroy(Entity entity) {
    //TODO!
}

} //End of namespace ecs
