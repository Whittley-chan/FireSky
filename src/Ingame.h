#pragma once
#include "Render.h"
#include <vector>

#ifndef INGAME_H
#define INGAME_H

constexpr float PLR_VELOCITY = 540.0f;
constexpr float ENM_VELOCITY = 250.0f;
constexpr Uint8 MAX_BULLET_NUM = 25;
constexpr Uint8 MAX_ENEMY_BULLET_NUM = 250;
constexpr Uint8 MAX_ENEMY_NUM = 8;

extern bool Paused;
extern bool Ended;
extern unsigned long int Score;
extern std::vector<unsigned long int> Highscores;

enum Target 
	{
		PLAYER = 0,
		ENEMY = 1
	};

void IngameMouseHandler(SDL_Event* event);

void IngameKeyboardHandler();

void CollsionCheck(Target target);

void UpdateEntity(Target target);

void SpawnBullet(Target target);

void UpdateBullet(Target target);

void IngameRender();

void Update();

#endif // !INGAME_H


;