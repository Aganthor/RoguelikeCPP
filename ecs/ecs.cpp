#include "ecs.h"

#include <cstring>

namespace ecs
{
////////////////////////////////////////////////////////////////////////////////
// Our destructor to take care of deleting our components and entitites.
////////////////////////////////////////////////////////////////////////////////
ECS::~ECS()
{
  for (ComponentMap::iterator it = m_components.begin(); it != m_components.end(); ++it)
  {
    std::uint32_t typeSize = BaseECSComponent::getTypeSize(it->first);
    ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(it->first);
    for (std::uint32_t i = 0; i < it->second.size(); i += typeSize)
    {
      freefn((BaseECSComponent*)&it->second[i]);
    }
  }
  //Delete the entities...
  for (auto i = 0; i < m_entities.size(); ++i)
  {
    delete m_entities[i];
  }
}

EntityHandle ECS::makeEntity(BaseECSComponent *entityComponents, const std::uint32_t *componentIDs, std::size_t numComponents)
{
  EntitiesVectorMemberData* newEntity = new EntitiesVectorMemberData;
  EntityHandle handle = (EntityHandle)newEntity;

  //components
  for (auto i = 0; i < numComponents; ++i)
  {
    //Check the componentid if it's valid
    if (!BaseECSComponent::isTypeValid(componentIDs[i]))
    {
      //TODO: Log error in some kind of error log.
      delete newEntity;
      return NULL_ENTITY_HANDLE;
    }

    addComponentInternal(handle, newEntity->second, componentIDs[i], &entityComponents[i]);
  }

  newEntity->first = m_entities.size();
  m_entities.push_back(newEntity);

  return handle;
}

void ECS::removeEntity(EntityHandle handle)
{
  std::vector<std::pair<std::uint32_t, std::uint32_t>>& entity = handleToEntity(handle);
  for (auto i = 0; i < entity.size(); ++i)
  {
    deleteComponent(entity[i].first, entity[i].second);
  }

  std::uint32_t destIndex = handleToEntityIndex(handle);
  std::uint32_t srcIndex = m_entities.size() - 1;
  delete m_entities[destIndex];
  m_entities[destIndex] = m_entities[srcIndex];
  m_entities.pop_back();
}

void ECS::deleteComponent(std::uint32_t componentID, std::uint32_t index)
{
  std::vector<std::uint8_t>& array = m_components[componentID];
  ECSComponentFreeFunction freefn = BaseECSComponent::getTypeFreeFunction(componentID);
  std::size_t typeSize = BaseECSComponent::getTypeSize(componentID);
  std::uint32_t srcIndex = array.size() - typeSize;

  BaseECSComponent* destComponent = (BaseECSComponent*)&array[index];
  BaseECSComponent* srcComponent = (BaseECSComponent*)&array[srcIndex];
  freefn(destComponent);

  if (index == srcIndex)
  {
    array.resize(srcIndex);
    return;
  }

  std::memcpy(destComponent, srcComponent, typeSize);

  //Update the components...
  std::vector<std::pair<std::uint32_t, std::uint32_t>>& srcComponents = handleToEntity(srcComponent->entity);
  for (auto i = 0; i < srcComponents.size(); ++i)
  {
    if (componentID == srcComponents[i].first && srcIndex == srcComponents[i].second)
    {
      srcComponents[i].second = index;
      break;
    }
  }
  array.resize(srcIndex);
}

bool ECS::removeComponentInternal(EntityHandle handle, std::uint32_t componentID)
{
    //Update the components...
  std::vector<std::pair<std::uint32_t, std::uint32_t>>& entityComponents = handleToEntity(handle);
  for (auto i = 0; i < entityComponents.size(); ++i)
  {
    if (componentID == entityComponents[i].first)
    {
      deleteComponent(entityComponents[i].first, entityComponents[i].second);
      std::uint32_t srcIndex = entityComponents.size() - 1;
      std::uint32_t destIndex = i;
      entityComponents[destIndex] = entityComponents[srcIndex];
      entityComponents.pop_back();
      return true;
    }
  }
  return false;
}

void ECS::addComponentInternal(EntityHandle handle, std::vector<std::pair<std::uint32_t, std::uint32_t> > &entity, std::uint32_t componentID, BaseECSComponent *component)
{
    ECSComponentCreateFunction createfn = BaseECSComponent::getTypeCreateFunction(componentID);
    std::pair<std::uint32_t, std::uint32_t> newPair;
    newPair.first = componentID;
    newPair.second = createfn(m_components[componentID], handle, component);
    entity.push_back(newPair);
}

BaseECSComponent* ECS::getComponentInternal(std::vector<std::pair<std::uint32_t, std::uint32_t> > &entityComponents, std::uint32_t componentID)
{
  for (auto i = 0; i < entityComponents.size(); ++i)
  {
    if (componentID == entityComponents[i].first)
    {
      return (BaseECSComponent*)& m_components[componentID][entityComponents[i].second];
    }
  }

  return nullptr;
}


}//Namespace
