#include "Entity.h"

#include <cmath>
#include <type_traits>
#include <typeinfo>

#include "Component.h"

namespace ecs {

//Entity::Entity(int x, int y, const std::string& name, char visual, TCODColor color, bool blocks)
//    : m_xPos{ x },
//    m_yPos{ y },
//    m_Name{ name },
//    m_Visual {visual },
//    m_Color{ color },
//    m_Blocks{ blocks }
//{
//}

Entity::~Entity()
{
    for (auto& c : m_components) {
        delete c.second;
    }
}


void Entity::addComponent(std::type_index type, Component* c)
{
    m_components[type] = c;
}

/////////////////////////////////////////////////////////////////////////////////
//// As the name suggest, will calculate the distance between this and target.
/////////////////////////////////////////////////////////////////////////////////
//double Entity::DistanceTo(Entity& target)
//{
//    auto dx = int{0};
//    auto dy = int{0};

//    dx = target.getXPos() - m_xPos;
//    dy = target.getYPos() - m_yPos;

//    return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
//}

//void Entity::addComponent(std::unique_ptr<Component> component)
//{
//    //TODO : Not sure how to do it...
//    //static_assert(std::is_base_of<Component, component>::value,
//    //"`component` must be derived from `Component`");

//    auto alreadyThere = m_components.find(component.get()->getName());

//    if (alreadyThere != m_components.end())
//        return;

//    m_components.emplace(std::make_pair(component.get()->getName(), std::move(component)));
//}


} // namespace ecs
