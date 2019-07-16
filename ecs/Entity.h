#pragma once

#include <cstdint>

namespace ecs {

using EntityID = std::int32_t;
constexpr auto MaxEntityCount = 1024;

//Simple struct to represent an ID.

struct Entity {
    EntityID id;
};

} // namespace ecs

