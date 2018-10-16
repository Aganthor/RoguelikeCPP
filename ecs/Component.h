#pragma once

#include <string>

///////////////////////////////////////////////////////////////////////////////
// A generic component class.
///////////////////////////////////////////////////////////////////////////////

class Component
{
public:
    Component() { m_name = ""; };
    Component(const std::string& name) : m_name{name} {}
    ~Component() {}

    virtual void TakeTurn(float delta) = 0;

    const std::string& getName() { return m_name; }
protected:
    std::string m_name;
};
