#pragma once

#include <cstdint>

namespace ecs {

class World;

struct Entity {
    std::uint32_t id;

    //To put it in maps.
    friend bool operator<(const Entity& l, const Entity& r) { return l.id < r.id; }
};

} // namespace ecs

