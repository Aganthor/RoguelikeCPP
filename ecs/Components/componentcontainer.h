#pragma once

#include <vector>
#include <bitset>
#include <unordered_map>

#include "../Entity.h"

namespace ecs {

//
// Base class so that we can add all the COmponentContainer into one
// container.
//
class BaseComponentContainer {
public:
    virtual ~BaseComponentContainer() = default;

    virtual void reserve(std::size_t size) = 0;
    virtual bool tryRemove(Entity entity) = 0;
};

//
// ComponentContainer so that we can have a contiguous place to store all
// of components of the same type.
//
template <typename T, std::size_t ComponentCount, std::size_t SystemCount>
class ComponentContainer : public BaseComponentContainer {
public:
    ComponentContainer(std::vector<std::bitset<ComponentCount>>& entityToBitset) :
        m_entityToBitset{entityToBitset} {}

    virtual void reserve(std::size_t size) override {
        m_components.reserve(size);
        m_componentToEntity.reserve(size);
        m_entityToComponent.reserve(size);
    }

    T& get(Entity entity) {
        return m_components[m_entityToComponent[entity]];
    }
    const T& get(Entity entity) const {
        return m_components[m_entityToComponent.find(entity)->second];
    }

    template <typename... Args>
    void add(Entity entity, Args&&... args) {
        auto index = static_cast<Index>(m_components.size());
        m_components.emplace_back(std::forward<Args>(args)...);
        m_componentToEntity.emplace_back(entity);
        m_entityToComponent[entity] = index;
        m_entityToBitset[entity][T::type] = true;
    }

    void remove(Entity entity) {
        m_entityToBitset[entity][T::type] = false;
        auto index = m_entityToComponent[entity];

        m_components[index] = std::move(m_components.back());
        m_components.pop_back();

        m_entityToComponent[m_componentToEntity.back()] = index;
        m_entityToComponent.erase(entity);

        m_componentToEntity[index] = m_componentToEntity.back();
        m_componentToEntity.pop_back();

    }

    virtual bool tryRemove(Entity entity) override {
        if (m_entityToBitset[entity][T::type]) {
            remove(entity);
            return true;
        }

        return false;
    }

    Entity getOwner(const T& component) const {
        auto begin = m_components.data();
        auto index = static_cast<std::size_t>(&component - begin);

        return m_componentToEntity[index];
    }

private:
    std::vector<T> m_components;
    std::vector<Entity> m_componentToEntity;
    std::unordered_map<Entity, Index> m_entityToComponent;
    std::vector<std::bitset<ComponentCount>>& m_entityToBitset;
};

} //Namespace ecs
