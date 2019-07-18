#pragma once

#include <bitset>
#include <cstdint>
#include <numeric>
#include <vector>

#include "Entity.h"

namespace ecs {

// using Entity = std::uint32_t;

template <std::size_t ComponentCount, std::size_t SystemCount>
class EntityContainer {
 public:
  void reserve(std::size_t size) {
    m_freeEntities.resize(size);
    std::iota(std::begin(m_freeEntities), std::end(m_freeEntities), 0);
    m_entityToBitset.resize(size);
  }

  std::vector<std::bitset<ComponentCount>>& getEntityToBitset() {
    return m_entityToBitset;
  }

  const std::bitset<ComponentCount>& getSignature(Entity entity) const {
    return m_entityToBitset[entity];
  }

  Entity create() {
    auto entity = Entity();
    if (m_freeEntities.empty()) {
      entity = static_cast<Entity>(m_entityToBitset.size());
      m_entityToBitset.emplace_back();
    } else {
        entity = m_freeEntities.back();
        m_freeEntities.pop_back();
        m_entityToBitset[entity].reset();
    }
    return entity;
  }

  void remove(Entity entity) {
      m_freeEntities.push_back(entity);
  }

 private:
  std::vector<std::bitset<ComponentCount>> m_entityToBitset;
  std::vector<Entity> m_freeEntities{};
};

}  // Namespace ecs
