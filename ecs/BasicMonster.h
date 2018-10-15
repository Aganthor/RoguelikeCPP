#pragma once

#include "Component.h"

class BasicMonster : public Component
{
public:
    BasicMonster() {};
    ~BasicMonster() {};

    void TakeTurn(float delta) override;
private:
};
