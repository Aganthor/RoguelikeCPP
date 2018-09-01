#pragma once

#include <map>
#include "ecsComponent.h"
#include "ecsSystem.h"

namespace ecs
{
class ECS
{
public:
  ECS(){}
  ~ECS();

  //Entity methods
  EntityHandle makeEntity(BaseECSComponent* components, const std::uint32_t* componentIDs, std::size_t numComponents);
  void removeEntity(EntityHandle handle);

  //Components methods
  template<class Component>
      void addComponent(EntityHandle handle, Component* component);

  template<class Component>
  void removeComponent(EntityHandle handle);

  template<class Component>
  void addComponent(EntityHandle handle);

  //System methods
  inline void addSystem(BaseECSSystem& system)
  {
    m_systems.push_back(&system);
  }
  void updateSystems(float delta);
  void removeSystem(BaseECSSystem& system);

private:
  std::vector<BaseECSSystem*> m_systems;
  std::map<std::uint32_t, std::vector<std::uint8_t>> m_components;
  std::vector<std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* > m_entities;

  inline std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>* handleToRawType(EntityHandle handle)
  {
    return (std::pair<std::uint32_t, std::vector<std::pair<std::uint32_t, std::uint32_t>>>*)handle;
  }

  inline std::uint32_t handleToEntityIndex(EntityHandle handle)
  {
    return handleToRawType(handle)->first;
  }

  inline std::vector<std::pair<std::uint32_t, std::uint32_t>>& handleToEntity(EntityHandle handle)
  {
    return handleToRawType(handle)->second;
  }
};
}
