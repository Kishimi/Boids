#pragma once

#include <vector>

#include <cmath>

#include "Math.hpp"
#include "Obstacle.hpp"
#include "olcPixelGameEngine.h"

class Boid final
{
public:
	static constexpr float speed = 100.0f;
	static constexpr float turnSpeed = 6.0f;
	static constexpr float visionRange = 75.0f;
	static constexpr float alignment = 1.0f;
	static constexpr float coherence = 1.0f;
	static constexpr float seperation = 4.0f;
	static constexpr float obstacleAvoidance = 12.0f;

public:
	void Update(const std::vector<Boid> &nearbyBoids, const std::vector<Obstacle> &nearbyObstacles, const float dt);

	void SetPosition(const olc::vf2d &position);
	olc::vf2d GetPosition() const;

	void SetVelocity(const olc::vf2d &velocity);
	olc::vf2d GetVelocity() const;

	float Distance(const Boid &otherBoid) const;

private:
	void Steer(const olc::vf2d &desiredVelocity, const float dt, const float modifier = 1.0f);
	void Align(const std::vector<Boid> &nearbyBoids, const float dt);
	void Cohere(const std::vector<Boid> &nearbyBoids, const float dt);
	void Seperate(const std::vector<Boid> &nearbyBoids, const float dt);
	void Avoid(const std::vector<Obstacle> &nearbyObstacles, const float dt);

private:
	olc::vf2d position;
	olc::vf2d velocity;
};