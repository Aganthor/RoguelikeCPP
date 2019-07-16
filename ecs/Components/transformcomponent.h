#pragma once

#include "Component.h"

namespace ecs {

//
// Transform component : representing the entity in the world.
//

class TransformComponent : public Component<TransformComponent> {
public:
    int x {0};
    int y {0};
};

}
