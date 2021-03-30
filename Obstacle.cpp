#include "Obstacle.hpp"

void Obstacle::SetPosition(const olc::vf2d &position)
{
	this->position = position;
}

olc::vf2d Obstacle::GetPosition() const
{
	return position;
}