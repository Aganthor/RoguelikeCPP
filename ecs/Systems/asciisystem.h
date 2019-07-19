#pragma once

#include "system.h"
#include "../entitymanager.h"
#include "../Components/asciicomponent.h"

namespace ecs {

class AsciiSystem : public System<ComponentCount, SystemCount> {
public:
    AsciiSystem(EntityManager<ComponentCount, SystemCount>& entityManager) : m_entityManager{entityManager} {
        setSignature<AsciiComponent>();
    }

    void update(float dt) {
        for (const auto& entity : getManagedEntitites()) {
            auto ascii = getComponent(entity);
        }
    }

private:
    EntityManager<ComponentCount, SystemCount>& m_entityManager;
};


} //namespace ecs
