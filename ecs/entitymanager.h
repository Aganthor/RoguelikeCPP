#pragma once

#include <unordered_map>
#include <array>
#include <memory>
#include <tuple>

#include "ecs.h"
#include "Entity.h"
#include "Components/Component.h"
#include "Components/componentcontainer.h"
#include "Systems/system.h"
#include "entitycontainer.h"

namespace ecs {
//
// The EntityManager is responsible to glue all of the ECS components together.
//

template <std::size_t ComponentCount, std::size_t SystemCount>
class EntityManager {
public:
    template<typename T>
    void registerComponent() {
        checkComponentType<T>();
        m_componentContainers[T::type] = std::make_unique<ComponentContainer<T,
                ComponentCount, SystemCount>>(m_entities.getEntityToBitset());
    }

    template<typename T, typename ...Args>
    T* createSystem(Args&& ...args) {
        auto type = m_systems.size();
        auto& system = m_systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        system->setUp(type);
        return static_cast<T*>(system.get());
    }

    void reserve(std::size_t size) {
        for (auto i = std::size_t(0); i < ComponentCount; ++i) {
            if (m_componentContainers[i])
                m_componentContainers[i]->reserve(size);
        }
        m_entities.reserve(size);
    }

    Entity createEntity() {
        return m_entities.create();
    }

    void removeEntity(Entity entity);

    template<typename T>
    bool hasComponent(Entity entity) const {
        checkComponentType<T>();
        return m_entities.getBitset(entity)[T::type];
    }

    template<typename ...Ts>
    bool hasComponents(Entity entity) const {
        checkComponentTypes<Ts...>();
        auto requirements = std::bitset<ComponentCount>();
        (requirements.set(Ts::type), ...);
        return (requirements & m_entities.getBitset(entity)) == requirements;
    }

    template<typename T>
    T& getComponent(Entity entity) {
        checkComponentType<T>();
        return getComponentContainer<T>()->get(entity);
    }

    template<typename T>
    const T& getComponent(Entity entity) const {
        checkComponentType<T>();
        return getComponentContainer<T>()->get(entity);
    }

    template<typename ...Ts>
    std::tuple<Ts&...> getComponents(Entity entity) {
        checkComponentTypes<Ts...>();
        return std::tie(getComponentContainer<Ts>()->get(entity)...);
    }

    template<typename ...Ts>
    std::tuple<const Ts&...> getComponents(Entity entity) const;

    template<typename T, typename... Args>
    void addComponent(Entity entity, Args&&... args) {
        checkComponentType<T>();
        getComponentContainer<T>()->add(entity, std::forward<Args>(args)...);
        //Send message to systems.
        const auto& bitset = m_entities.getBitset(entity);
        for (auto& system : m_systems) {
            system->onEntityUpdated(entity, bitset);
        }
    }

    template<typename T>
    void removeComponent(Entity entity) {
        checkComponentType<T>();
        getComponentContainer<T>()->remove(entity);
        //Send message to systems
        const auto& bitset = m_entities.getBitset(entity);
        for (auto& system : m_systems) {
            system->onEntityUpdated(entity, bitset);
        }
    }

    template<typename T>
    Entity getOwner(const T& component) const {
        checkComponentType<T>();
        return getComponentContainer<T>()->getOwner(component);
    }

private:
    std::array<std::unique_ptr<BaseComponentContainer>, ComponentCount> m_componentContainers;
    EntityContainer<ComponentCount, SystemCount> m_entities;
    std::vector<std::unique_ptr<System<ComponentCount, SystemCount>>> m_systems;

    //
    //A set of helper fonctions.
    //

    template<typename T>
    void checkComponentType() const {
        static_assert (std::is_base_of_v<Component<T>, T>);
    }

    template<typename ...Ts>
    void checkComponentTypes() const {
        (checkComponentType<Ts>(), ...);
    }

    template<typename T>
    auto getComponentContainer() {
        return static_cast<ComponentContainer<T, ComponentCount, SystemCount>*>(m_componentContainers[T::type].get());
    }

    template<typename T>
    auto getComponentContainer() const {
        return static_cast<ComponentContainer<T, ComponentCount, SystemCount>*>(m_componentContainers[T::type].get());
    }
};

} //namespace ecs
