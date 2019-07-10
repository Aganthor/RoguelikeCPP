#pragma once

#include <cstdint>

namespace ecs {

//A simple struct with a simple unsigned int id.
struct Entity {
    std::uint32_t id;
};

//The maximum number of entities that the system can handle.
const Entity MAX_ENTITIES = 5000;

} // namespace ecs

