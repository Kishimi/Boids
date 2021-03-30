#pragma once

#include <random>
#include <cmath>

#include "olcPixelGameEngine.h"

namespace Math
{

constexpr float pi = 3.1415926535f;

constexpr float ToDeg(const float radians)
{
	return radians * (180.0f / pi);
}

inline float Angle(const olc::vf2d &lhs, const olc::vf2d &rhs)
{
	return ToDeg(std::acos(std::fabs(lhs.dot(rhs)) / (lhs.mag() * rhs.mag())));
}

inline void SetMagnitude(olc::vf2d &vec, const float magnitude)
{
	vec = vec.norm() * magnitude;
}

inline int Random(const int min, const int max)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(engine);
}

}