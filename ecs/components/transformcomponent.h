#pragma once

namespace ecs {

//
// Transform component : representing the entity in the world.
//

struct TransformComponent {
    TransformComponent(int pX, int pY) : x{pX}, y{pY} {}

    int x {0};
    int y {0};
};

}
