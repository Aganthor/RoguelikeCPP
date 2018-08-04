#pragma once

#include "Component.h"

class Fighter : public Component
{
public:
    Fighter(int hp, int defense, int power) : m_MaxHP{hp}, m_HP{hp}, 
                                              m_Defense{defense}, m_Power{power} 
    {
    }
    ~Fighter() {};

    void TakeTurn(float delta) override;

private:
    int m_MaxHP;
    int m_HP;
    int m_Defense;
    int m_Power;
};