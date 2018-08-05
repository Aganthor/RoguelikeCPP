#include "ecsComponent.h"

namespace ecs
{
    static std::uint32_t componentID = 0;

    static std::uint32_t nextID()
    {
        return componentID++;
    }
}