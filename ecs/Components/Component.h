#pragma once

#include <cstdint>

namespace ecs {

static constexpr auto MaxComponent = 32;

//
//Generic Component. A automatic Type ID is generated fdor each.
//

template <typename T>
class Component {
public:
    static const std::size_t type;
};

std::size_t generateComponentType() {
    static auto counter = std::size_t{0};
    return counter++;
}

template <typename T>
const std::size_t Component<T>::type = generateComponentType();

} // namespace ecs
