#pragma once

namespace ecs {

//
// Position component : representing the entity in the world.
//

struct PositionComponent {
    PositionComponent(int pX, int pY) : x{pX}, y{pY} {}

    int x {0};
    int y {0};
};

}
