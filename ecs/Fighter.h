#pragma once

#include "Component.h"

class FighterComponent : public Component
{
public:
    FighterComponent(int hp, int defense, int power) : Component("FighterAI"), m_MaxHP{hp}, m_HP{hp},
                                              m_Defense{defense}, m_Power{power}
    {
    }
    virtual ~FighterComponent() {}

    void TakeTurn(float delta) override;

private:
    int m_MaxHP;
    int m_HP;
    int m_Defense;
    int m_Power;
};
