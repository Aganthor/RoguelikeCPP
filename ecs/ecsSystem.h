#pragma once

#include "ecsComponent.h"

#include <cstdint>
#include <vector>

namespace ecs
{

class BaseECSSystem
{
public:
  BaseECSSystem(const std::vector<std::uint32_t>& componentTypesIn) : m_componentTypes{componentTypesIn} {}
  virtual void updateComponents(float delta, BaseECSComponent** components) {}
  const std::vector<std::uint32_t>& getComponentTypes()
  {
    return m_componentTypes;
  }

private:
  std::vector<std::uint32_t> m_componentTypes;
};

}
