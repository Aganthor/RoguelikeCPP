#pragma once

#include "Component.h"

namespace ecs {

class HealthComponent : public Component<HealthComponent> {
public:
    HealthComponent() : curHP{0}, maxHP{0} {}
    HealthComponent(int cur, int max) : curHP{cur}, maxHP{max} {}

public:
    int curHP {0};
    int maxHP {0};
};

}
