#pragma once

#include "../components/asciicomponent.h"
#include "../EntityManager.h"

namespace ecs {

class AsciiSystem {
public:
    AsciiSystem(EntityManager& entityManager) : m_entityManager{entityManager} {
    }

    void update(float dt) {
    }

private:
    EntityManager& m_entityManager;
};


} //namespace ecs
