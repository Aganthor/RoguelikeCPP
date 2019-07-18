#pragma once

#include <bitset>
#include <vector>
#include <unordered_map>

#include "../Entity.h"
#include "../entitymanager.h"
#include "../Components/Component.h"

namespace ecs {

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
        (m_systemSignature.set(Ts::type);
    }

    const std::vector<Entity>& getManagedEntities() const;

    virtual void onManagedEntityAdded([[maybe_unused]] Entity entity);
    virtual void onManagedEntityRemoved([[maybe_unused]] Entity entity);

private:
    friend EntityManager<ComponentCount, SystemCount>;

    void setUp(std::size_t type);
    void onEntityUpdated(Entity entity, const std::bitset<ComponentCount>& components);
    void onEntityRemoved(Entity entity);
    void addEntity(Entity entity);
    void removeEntity(Entity entity);

    std::bitset<MaxComponent> m_systemSignature;
    std::size_t m_type;
    std::vector<Entity> m_managedEntities;
    std::unordered_map<Entity, Index> m_entityToManagedEntity;
};

} //Namespace ecs
