#pragma once

#include "Component.h"

class BasicMonsterAIComponent : public Component
{
public:
    BasicMonsterAIComponent() : Component{"BasicMonsterAI"} {}
    virtual ~BasicMonsterAIComponent() override {}

    void TakeTurn(float delta) override;
private:
};
