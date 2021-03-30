#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <cstdlib>
#include <ctime>

#include "Boid.hpp"
#include "Obstacle.hpp"

class App final : public olc::PixelGameEngine
{
public:
	bool OnUserCreate() override
	{
		sAppName = "Boids";

		// Create boids
		for (int i = 0; i < 200; i++)
		{
			Boid boid;
			boid.SetPosition(olc::vf2d(Math::Random(0, this->ScreenWidth()), Math::Random(0, this->ScreenHeight())));

			olc::vf2d randomVelocity(Math::Random(-100, 100), Math::Random(-100, 100));
			Math::SetMagnitude(randomVelocity, Boid::speed);
			boid.SetVelocity(randomVelocity);

			boids.push_back(boid);
		}

		// Create obstacles
		for (int i = 0; i < 15; i++)
		{
			Obstacle obstacle;
			obstacle.SetPosition(olc::vf2d(Math::Random(0, this->ScreenWidth()), Math::Random(0, this->ScreenHeight())));

			obstacles.push_back(obstacle);
		}

		return true;
	}

	bool OnUserUpdate(const float dt) override
	{
		this->Clear(olc::BLACK);

		for (Boid &boid : boids)
		{
			std::vector<Boid> nearbyBoids;
			for (const Boid &otherBoid : boids)
			{
				if (boid.GetPosition() != otherBoid.GetPosition() && boid.Distance(otherBoid) <= boid.visionRange)
				{
					// this->DrawLine(boid.GetPosition(), otherBoid.GetPosition(), olc::DARK_GREY);
					nearbyBoids.push_back(otherBoid);
				}
			}

			std::vector<Obstacle> nearbyObstacles;
			for (const Obstacle &obstacle : obstacles)
			{
				if ((boid.GetPosition() - obstacle.GetPosition()).mag() <= boid.visionRange)
				{
					nearbyObstacles.push_back(obstacle);
				}
			}

			this->WrapPosition(boid);

			boid.Update(nearbyBoids, nearbyObstacles, dt);
		}

		for (const Boid &boid : boids)
		{
			this->DrawBoid(boid);
		}

		for (const Obstacle &obstacle : obstacles)
		{
			this->DrawObstacle(obstacle);
		}

		return true;
	}

private:
	void DrawBoid(const Boid &boid)
	{
		this->FillCircle(boid.GetPosition(), 2.0f);
	}

	void DrawObstacle(const Obstacle &obstacle)
	{
		this->FillCircle(obstacle.GetPosition(), 3.0f, olc::RED);
	}

	void WrapPosition(Boid &boid)
	{
		olc::vf2d pos = boid.GetPosition();
		if (pos.x < 0.0f)
			pos.x = this->ScreenWidth();
		else if (pos.x >= this->ScreenWidth())
			pos.x = 0.0f;

		if (pos.y < 0.0f)
			pos.y = this->ScreenHeight();
		else if (pos.y >= this->ScreenHeight())
			pos.y = 0.0f;

		boid.SetPosition(pos);
	}

private:
	std::vector<Boid> boids;
	std::vector<Obstacle> obstacles;
};

int main()
{
	App app;
	if (app.Construct(1920, 1080, 1, 1))
		app.Start();

	return 0;
}
