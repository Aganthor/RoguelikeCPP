#pragma once

namespace ecs {

struct HealthComponent {
    HealthComponent() : curHP{0}, maxHP{0} {}
    HealthComponent(int cur, int max) : curHP{cur}, maxHP{max} {}

    int curHP {0};
    int maxHP {0};
};

}
