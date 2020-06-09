#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include "../3rdParty/glm/glm/vec3.hpp"
#pragma warning(pop)

template <class T>
inline void SafeDelete(T& pointer)
{
	if (pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}

struct GameTime
{
	int FPS;
	float elapsedSec;
};