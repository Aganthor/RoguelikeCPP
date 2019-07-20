#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>

#include "../Entity.h"

namespace ecs {

template <std::size_t ComponentCount, std::size_t SystemCount>
class EntityManager;

template <std::size_t ComponentCount, std::size_t SystemCount>
class System {
public:
    virtual ~System() = default;

protected:
    //
    //Fold expression to set all the bits of the bitset to represent the
    //proper Component signature of the system.
    //
    template <typename ...Ts>
    void setSignature() {
        (m_systemSignature.set(Ts::type), ...);
    }

    const std::vector<Entity>& getManagedEntities() const {
        return m_managedEntities;
    }

    virtual void onManagedEntityAdded([[maybe_unused]] Entity entity);
    virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity);

private:
    friend EntityManager<ComponentCount, SystemCount>;

    void setUp(std::size_t type) { m_type = type; }

    void onEntityUpdated(Entity entity, const std::bitset<ComponentCount>& components) {
        auto satisfied = (m_systemSignature & components) == m_systemSignature;
        auto managed = m_entityToManagedEntity.find(entity) != std::end(m_entityToManagedEntity);

        if (satisfied && !managed)
            addEntity(entity);
        else if (!satisfied && managed)
            removeEntity(entity);
    }

    void onEntityRemoved(Entity entity) {
        if (m_entityToManagedEntity.find(entity) != std::end(m_entityToManagedEntity))
            removeEntity(entity);
    }

    void addEntity(Entity entity) {
        m_entityToManagedEntity[entity] = static_cast<Index>(m_managedEntities.size());
        m_managedEntities.emplace_back(entity);
        onManagedEntityAdded(entity);
    }

    void removeEntity(Entity entity) {
        onManagedEntityRemoved(entity);
        auto index = m_entityToManagedEntity[entity];
        m_entityToManagedEntity[m_managedEntities.back()] = index;
        m_entityToManagedEntity.erase(entity);
        m_managedEntities[index] = m_managedEntities.back();
        m_managedEntities.pop_back();
    }

    std::bitset<ComponentCount> m_systemSignature;
    std::size_t m_type;
    std::vector<Entity> m_managedEntities;
    std::unordered_map<Entity, Index> m_entityToManagedEntity;
};

} //Namespace ecs
