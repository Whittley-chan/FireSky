#pragma once
#include "Render.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H

constexpr float DEFAULT_PLAYER_HP = 100;
constexpr float DEFAULT_ENEMY_HP = 100.0f;
constexpr float DEFAULT_PLAYER_DAMAGE = 1000.0f;
constexpr float DEFAULT_ENEMY_DAMAGE = 8.0f;
constexpr float DEFAULT_PROJECTILE_VELOCITY = 0.75f;
constexpr float DEFAULT_GUN_COOLDOWN = 200.0f;
constexpr float DEFAULT_ENEMY_GUN_COOLDOWN = 1200.0f;
constexpr float DEFAULT_ENEMY_MOVEMENT_COOLDOWN = 750.0f;

enum Movement
	{
		UNKNOWN = 0,
		LEFT = 1,
		RIGHT = 2
	};

enum EnemyType
	{
		Type_1 = 1,
		Type_2 = 2,
		Type_3 = 3

	};

class Bullet
	{
		public:
			SDL_FRect* hitbox;
			SDL_Texture* texture;

			float Damage = DEFAULT_PLAYER_DAMAGE;
			float headingX = NULL;
			float headingY = NULL;

			bool active = false;

			Bullet() = default;
			Bullet(SDL_FRect* _hitbox, SDL_Texture* texture);

	};

class Player
	{
		public:
			float HP = DEFAULT_PLAYER_HP;

			SDL_FRect* hitbox;
			SDL_Texture* texture;

			float cooldown = DEFAULT_GUN_COOLDOWN;
			bool isMoving = false;
			Movement Direction = UNKNOWN;

			Player(SDL_FRect* _hitbox, SDL_Texture* _texture);

			void Fire();
			void Move(float velocity);

	};

class Enemy
	{
		public:
			float HP = DEFAULT_ENEMY_HP;
			SDL_FRect* hitbox;
			SDL_Texture* texture;
			
			float movementCooldown = DEFAULT_ENEMY_MOVEMENT_COOLDOWN;	
			float gunCooldown = DEFAULT_ENEMY_GUN_COOLDOWN;
			float destination = NULL;
			Movement Direction = UNKNOWN;
			
			bool inMovementCooldown = false;
			bool active = false;
			void Fire();
			void Move(float velocity);


			Enemy(SDL_FRect* _hitbox, SDL_Texture* _texture);
	}; 


extern std::vector<Bullet*> PlayerBulletPool;
extern std::vector<Bullet*> EnemyBulletPool;
extern std::vector<Enemy*> EnemyPool;

extern Player* player;

extern Movement getRandomMovement();

#endif // !ENTITY_H


