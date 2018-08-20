#include "ecsComponent.h"

namespace ecs
{
    static std::uint32_t componentID = 0;

     std::uint32_t BaseECSComponent::nextID()
    {
        return componentID++;
    }
}