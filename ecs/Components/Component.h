#pragma once

#include <cstdint>
#include <type_traits>

#include "componentManager.h"
#include "../Entity.h"

//
//The base implementation of a component.
//

namespace ecs {

struct ComponentCounter {
    static int familyCounter;
};

template <typename ComponentType>
struct Component {
    static inline int family() {
        static int family = ComponentCounter::familyCounter++;
        return family;
    }
};

template <typename C>
static int GetComponentFamily() {
    return Component<typename std::remove_const<C>::type>::family();
}

} // namespace ecs
