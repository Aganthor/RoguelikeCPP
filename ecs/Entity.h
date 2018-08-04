#pragma once

#include <string>
#include <libtcod.hpp>

///////////////////////////////////////////////////////////////////////////////
// A generic object to represent players, enemies, items, etc.
///////////////////////////////////////////////////////////////////////////////

class Entity
{
public:
	Entity() = delete;
	Entity(int x, int y, const std::string& name, char visual, TCODColor color, bool blocks = false);
	~Entity();

	void Move(int dx, int dy)
	{
		m_xPos += dx;
		m_yPos += dy;
    }
	//void MoveTowards(int target_x, int target_y, );
	//void MoveAstar();
	double DistanceTo(Entity& target);

	//Getters
	int getXPos() { return m_xPos; }
	int getYPos() { return m_yPos; }
	const std::string& getName() { return m_Name; }
	char getVisual() { return m_Visual; }
	bool isBlocking() { return m_Blocks; }
	TCODColor getColor() { return m_Color; }

protected:
	int m_xPos;
	int m_yPos;
	std::string m_Name;
	char m_Visual;
	bool m_Blocks; //Can we pass through this entity?
	TCODColor m_Color;
};

