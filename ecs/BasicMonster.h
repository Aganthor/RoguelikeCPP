#pragma once

#include "Component.h"

class BasicMonster : public Component
{
public:
    BasicMonster() {};
    ~BasicMonster() {};

    virtual void TakeTurn(float delta) override;
private:
};