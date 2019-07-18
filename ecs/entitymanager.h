#pragma once

#include <unordered_map>
#include <array>
#include <memory>

#include "Entity.h"
#include "Components/Component.h"
#include "Systems/system.h"

//
// The EntityManager is responsible to glue all of the ECS components together.
//

//What should it do:
// - With entities:
    // - add an entity
    // - delete an entity
    // - check if an entity exists
    // - delete an entity
    // - add a component to an entity
    // - remove a component of an entity
// - With Systems :
// - Add a system
// - remove a system
////////////////////////////////
namespace ecs {

class EntityManager {
public:
    EntityManager();

private:
    Entity id;

};

}
