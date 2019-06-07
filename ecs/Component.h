#pragma once

#include <string>

namespace ecs {

class Entity;

///////////////////////////////////////////////////////////////////////////////
// A generic component class.
///////////////////////////////////////////////////////////////////////////////

class Component
{
public:
    Component() : m_name{""} {}
    Component(const std::string& name) : m_name{name} {}
    virtual ~Component() {}

    virtual void TakeTurn(float delta) = 0;

    const std::string& getName() const { return m_name; }

    Entity* getEntity() { return m_entity; }
protected:
    std::string m_name;
    Entity* m_entity;
};


} // namespace ecs
