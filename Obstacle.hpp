#pragma once

#include "olcPixelGameEngine.h"

class Obstacle final
{
public:
	void SetPosition(const olc::vf2d &position);
	olc::vf2d GetPosition() const;

private:
	olc::vf2d position;
};