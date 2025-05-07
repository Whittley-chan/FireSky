<<<<<<< HEAD
#pragma once
#include "Render.h"


#ifndef INGAME_H
#define INGAME_H

constexpr float PLR_VELOCITY = 540.0f;
constexpr float ENM_VELOCITY = 250.0f;
constexpr Uint8 MAX_BULLET_NUM = 25;
constexpr Uint8 MAX_ENEMY_BULLET_NUM = 150;
constexpr Uint8 MAX_ENEMY_NUM = 8;

extern bool Paused;

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


=======
#pragma once
#include "Render.h"


#ifndef INGAME_H
#define INGAME_H

constexpr float PLR_VELOCITY = 5400.0f;
constexpr float ENM_VELOCITY = 250.0f;
constexpr Uint8 MAX_BULLET_NUM = 25;
constexpr Uint8 MAX_ENEMY_BULLET_NUM = 150;
constexpr Uint8 MAX_ENEMY_NUM = 8;

extern bool Paused;

enum Target 
	{
		PLAYER = 0,
		ENEMY = 1
	};

void IngameMouseHandler(SDL_Event* event);

void IngameKeyboardHandler(SDL_Event* event);

void CollsionCheck(Target target);

void UpdateEntity(Target target);

void SpawnBullet(Target target);

void UpdateBullet(Target target);

void IngameRender();

void Update();

void IngameChangeState(GameContext context);

#endif // !INGAME_H


>>>>>>> 8efbb6131e1c3c2e4adf6c29c57f71e25ce283d1
;