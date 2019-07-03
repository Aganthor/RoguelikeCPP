#pragma once

namespace ecs {

class Entity;

///////////////////////////////////////////////////////////////////////////////
// A generic component class.
///////////////////////////////////////////////////////////////////////////////


struct Component
{
    Entity* entity;

    virtual void init() {}
    virtual void update(float mDT) {}
    virtual void draw() {}

    virtual ~Component() {}
};


} // namespace ecs
