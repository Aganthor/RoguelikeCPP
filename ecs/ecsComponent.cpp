#include "ecsComponent.h"

namespace ecs
{

std::vector<std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, std::size_t>> BaseECSComponent::componentTypes;

std::uint32_t BaseECSComponent::registerComponentType(ECSComponentCreateFunction createfn,
                                                      ECSComponentFreeFunction freefn, std::size_t size)
{
  std::uint32_t componentID = componentTypes.size();
  componentTypes.push_back(std::tuple<ECSComponentCreateFunction, ECSComponentFreeFunction, std::size_t>(createfn, freefn, size));
  return componentID;
}
}
