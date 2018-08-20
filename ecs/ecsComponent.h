#pragma once

#include <cstdint>
#include <vector>

namespace ecs
{
    //Forward declare.
    struct BaseECSComponent;

    using EntityHandle = void*;
    using ECSComponentCreateFunction = std::uint32_t (*)(std::vector<std::uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp);
    using ECSComponentFreeFunction = void (*)(BaseECSComponent* com);
    #define NULL_ENTITY_HANDLE nullptr;

    struct BaseECSComponent
    {
        static std::uint32_t nextID();
        EntityHandle entity = NULL_ENTITY_HANDLE;
    };

    template<typename T>
    struct ECSComponent : public BaseECSComponent
    {
        static const ECSComponentCreateFunction CREATE_FUNCTION;
        static const ECSComponentFreeFunction FREE_FUNCTION;
        static const std::uint32_t ID;
        static const std::size_t SIZE;
    };

    template<typename Component>
    std::uint32_t ECSComponentCreate(std::vector<std::uint8_t>& memory, EntityHandle entity, BaseECSComponent* comp)
    {
        std::uint32_t index = memory.size();
        memory.resize(index + Component::SIZE);
        Component* component = new(&memory[index])Component (*(Component*)comp);
        component->entity = entity;
        return index;
    }

    template<typename Component>
    void ECSComponentFree(BaseECSComponent* comp)
    {
        Component* component = (Component*)comp;
        component->~Component();
    }


    template<typename T>
    const std::uint32_t ECSComponent<T>::ID(BaseECSComponent::nextID());

    template<typename T>
    const std::size_t ECSComponent<T>::SIZE(sizeof(T));    

    template<typename T>
    const ECSComponentCreateFunction ECSComponent<T>::CREATE_FUNCTION(ECSComponentCreate<T>);

    template<typename T>
    const ECSComponentFreeFunction ECSComponent<T>::FREE_FUNCTION(ECSComponentFree<T>);    

    //Begin example code.
    struct TestComponent : public ECSComponent<TestComponent>
    {
        float x;
        float y;
    };
}