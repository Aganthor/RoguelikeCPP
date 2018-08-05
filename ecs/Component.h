#pragma once

///////////////////////////////////////////////////////////////////////////////
// A generic component class.
///////////////////////////////////////////////////////////////////////////////

class Component
{
public:
    Component() {};
    ~Component() {};

    virtual void TakeTurn(float delta) = 0;
private:
};