#include "Entity.h"

#include <cmath>

Entity::Entity(int x, int y, const std::string& name, char visual, TCODColor color, bool blocks)
	: m_xPos{ x }, 
	m_yPos{ y }, 
	m_Name{ name }, 
	m_Visual {visual },
	m_Color{ color },
	m_Blocks{ blocks }
{

}


Entity::~Entity()
{
}

///////////////////////////////////////////////////////////////////////////////
// As the name suggest, will calculate the distance between this and target.
///////////////////////////////////////////////////////////////////////////////

double Entity::DistanceTo(Entity& target)
{
	int dx, dy;

	dx = target.getXPos() - m_xPos;
	dy = target.getYPos() - m_yPos;

	return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}
