#include "ecs.h"

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

EntityHandle ECS::makeEntity(BaseECSComponent *components, const std::uint32_t *componentIDs, std::size_t numComponents)
{
  EntitiesVectorMemberData* newEntity = new EntitiesVectorMemberData;
  EntityHandle handle = (EntityHandle)newEntity;

  newEntity->first = m_entities.size();
  m_entities.push_back(newEntity);

  return handle;
}
}//Namespace
