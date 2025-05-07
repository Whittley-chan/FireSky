#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>


#include "graphics.h"
#include "Appstate.h"

#include "Render.h"
#include "Entity.h"
#include "Elements.h"

#include <cstdlib>
#include <iostream>

#include <string>
#include <cstring>
#include <random>
#include <type_traits>
#include <vector>

template <typename T>
T RNG(T a, T b) 
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());

		if constexpr (std::is_floating_point_v<T>) 
			{
				std::uniform_real_distribution<T> dis(a, b);
				return dis(gen);
			} 
		else if constexpr (std::is_integral_v<T>) 
			{
				std::uniform_int_distribution<T> dis(a, b);
				return dis(gen);
			} 
		else 
			{
				static_assert(std::is_arithmetic_v<T>, "Unsupported type");
			}
	}


extern constexpr Uint32 TARGET_FPS = 480;
extern constexpr float DELTA_TIME = 1000 / TARGET_FPS;

#endif // !MAIN_H

