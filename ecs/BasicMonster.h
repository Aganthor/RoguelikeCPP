#pragma once

#include "Component.h"

class BasicMonsterComponent : public Component
{
public:
    BasicMonsterComponent() : Component{"BasicMonsterAI"} {}
    ~BasicMonsterComponent() {}

    void TakeTurn(float delta) override;
private:
};
