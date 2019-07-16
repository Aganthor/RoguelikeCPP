#pragma once

#include <bitset>

#include "../Components/Component.h"

namespace ecs {

class System {
public:
    System() = default;

    //
    //Fold expression to set all the bits of the bitset to represent the
    //proper Component signature of the system.
    //
    template <typename ...Ts>
    void setSignature() {
        (m_systemSignature.set(Ts::type);
    }

protected:
    std::bitset<MaxComponent> m_systemSignature;
};
}
