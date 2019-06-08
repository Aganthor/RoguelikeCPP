#pragma once

#include <string>
#include <map>
#include <memory>
#include <algorithm>
#include <typeindex>

#include <libtcod.hpp>

namespace ecs {

//Forward declare.
class Component;

class Entity
{
public:
    Entity(const std::string& mType) : m_type{mType} {}
    ~Entity();

    void addComponent(std::type_index type, Component* c);

    template<typename T>
    T* getComponent()
    {
        auto it = m_components.find(std::type_index(typeid(T)));
        if (it != m_components.end())
        {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }

    void setType(const std::string& mType) { m_type = mType; }
    std::string getType() const { return m_type; }

private:
    std::string m_type;
    std::map<std::type_index, Component*> m_components;
};

///////////////////////////////////////////////////////////////////////////////
// A generic object to represent players, enemies, items, etc.
///////////////////////////////////////////////////////////////////////////////


//class Entity
//{
//public:
//    Entity() = delete;
//    Entity(int x, int y, const std::string& name, char visual, TCODColor color, bool blocks = false);
//    ~Entity();

//    void Move(int dx, int dy)
//    {
//        m_xPos += dx;
//        m_yPos += dy;
//    }
//    //void MoveTowards(int target_x, int target_y, );
//    //void MoveAstar();
//    double DistanceTo(Entity& target);

//    //Getters
//    int getXPos() { return m_xPos; }
//    int getYPos() { return m_yPos; }
//    const std::string& getName() { return m_Name; }
//    char getVisual() { return m_Visual; }
//    bool isBlocking() { return m_Blocks; }
//    TCODColor getColor() { return m_Color; }

//    //
//    // Searches the map for a component of typeid Component_t.
//    //
////    template <typename Component_t>
////    bool hasComponent(Component_t component)
////    {
////        auto component_present = std::find_if(m_components.begin(), m_components.end(), [component](const auto &c)
////        {
////            return c.second->get()->getName() == component.getName();
////        });

////        if (component_present != std::end(m_components))
////            return true;
////        else
////            return false;
////    }
//    void addComponent(std::unique_ptr<Component> component);

//protected:
//    int m_xPos;
//    int m_yPos;
//    std::string m_Name;
//    char m_Visual;
//    TCODColor m_Color;
//    bool m_Blocks; //Can we pass through this entity?

//    std::map<std::string, std::unique_ptr<Component>> m_components;
//};

} // namespace ecs

