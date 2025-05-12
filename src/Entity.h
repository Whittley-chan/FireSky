#pragma once

#include "Render.h"
#include <vector>

#ifndef ENTITY_H
#define ENTITY_H

constexpr float DEFAULT_PLAYER_HP = 100.0f;
constexpr float DEFAULT_ENEMY_HP = 100.0f;
constexpr float DEFAULT_PLAYER_DAMAGE = 12.0f;
constexpr float DEFAULT_ENEMY_DAMAGE = 8.0f;

constexpr float DEFAULT_ROCKET_DAMAGE = 300.0f;

constexpr float DEFAULT_BULLET_VELOCITY = 1.35f;
constexpr float DEFAULT_ROCKET_VELOCITY = 1.55f;

constexpr float DEFAULT_GUN_COOLDOWN = 300.0f;
constexpr float DEFAULT_ENEMY_GUN_COOLDOWN = 1300.0f;
constexpr float DEFAULT_ENEMY_MOVEMENT_COOLDOWN = 750.0f;
constexpr float DEFAULT_ROCKET_COOLDOWN = 3000.0f;




enum Movement
	{
		UNKNOWN = 0,
		LEFT = 1,
		RIGHT = 2,
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

			Bullet(SDL_FRect* _hitbox, SDL_Texture* texture);

	};

typedef class Rocket
	{
		public:
			SDL_FRect* Rect;
			SDL_FRect* ProximityFuseZone;
			SDL_Texture* texture;

			float Damage = DEFAULT_ROCKET_DAMAGE;

			float cooldown = 0.0f;

			bool active = false;

			Rocket(SDL_FRect* _Rect, SDL_Texture* texture);
			void Launch();
	} RKT;



class Player
	{
		public:
			float HP = DEFAULT_PLAYER_HP;

			SDL_FRect* hitbox;
			SDL_Texture* texture;

			bool GatlingUpgraded = false;
			bool RocketUpgraded = false;
			bool MissileUpgraded = false;

			float cooldown = DEFAULT_GUN_COOLDOWN;

			Player(SDL_FRect* _hitbox, SDL_Texture* _texture);

			void Fire();
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


#endif // !ENTITY_H


