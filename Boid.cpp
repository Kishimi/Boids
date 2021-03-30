#include "Boid.hpp"

void Boid::Update(const std::vector<Boid> &nearbyBoids, const std::vector<Obstacle> &nearbyObstacles, const float dt)
{
	if (!nearbyBoids.empty())
	{
		this->Align(nearbyBoids, dt);
		this->Cohere(nearbyBoids, dt);
		this->Seperate(nearbyBoids, dt);
	}

	if (!nearbyObstacles.empty())
	{
		this->Avoid(nearbyObstacles, dt);
	}

	// update position
	Math::SetMagnitude(velocity, speed);
	position += velocity * dt;
}

void Boid::SetPosition(const olc::vf2d &position)
{
	this->position = position;
}

olc::vf2d Boid::GetPosition() const
{
	return position;
}

void Boid::SetVelocity(const olc::vf2d &velocity)
{
	this->velocity = velocity;
}

olc::vf2d Boid::GetVelocity() const
{
	return velocity;
}

float Boid::Distance(const Boid &otherBoid) const
{
	return (otherBoid.position - position).mag();
}

void Boid::Steer(const olc::vf2d &desiredVelocity, const float dt, const float modifier)
{
	const olc::vf2d turningForce = desiredVelocity - velocity;

	velocity += turningForce * turnSpeed * modifier * dt;
}

void Boid::Align(const std::vector<Boid> &nearbyBoids, const float dt)
{
	// Calculate average velocity
	olc::vf2d averageVelocity;
	for (const Boid &boid : nearbyBoids)
	{
		averageVelocity += boid.velocity;
	}
	averageVelocity /= nearbyBoids.size();

	// Steer towards average angle
	this->Steer(averageVelocity, dt, alignment);
}

void Boid::Cohere(const std::vector<Boid> &nearbyBoids, const float dt)
{
	// Calculate average position
	olc::vf2d averagePosition;
	for (const Boid &boid : nearbyBoids)
	{
		averagePosition += boid.position;
	}
	averagePosition /= nearbyBoids.size();

	this->Steer(averagePosition - position, dt, coherence);
}

void Boid::Seperate(const std::vector<Boid> &nearbyBoids, const float dt)
{
	olc::vf2d avoidVelocity;
	for (const Boid &boid : nearbyBoids)
	{
		const olc::vf2d diff = position - boid.position;
		avoidVelocity += diff / diff.mag();
	}
	this->Steer(avoidVelocity, dt, seperation);
}

void Boid::Avoid(const std::vector<Obstacle> &nearbyObstacles, const float dt)
{
	olc::vf2d avoidVelocity;
	for (const Obstacle &obstacle : nearbyObstacles)
	{
		const olc::vf2d diff = position - obstacle.GetPosition();
		avoidVelocity += diff / diff.mag();
	}
	this->Steer(avoidVelocity, dt, obstacleAvoidance);
}