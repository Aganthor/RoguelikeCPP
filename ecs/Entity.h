#pragma once

#include <cstdint>
#include <limits>

namespace ecs {

using Entity = std::uint32_t;
using Index = std::uint32_t;

static constexpr auto InvalidIndex = std::numeric_limits<Index>::max();
  
} // namespace ecs

