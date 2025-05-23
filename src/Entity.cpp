#include "Entity.h"



Bullet::Bullet(SDL_FRect* _hitbox, SDL_Texture* _texture)
	{
		hitbox = _hitbox;
		texture = _texture;
	}

Rocket::Rocket(SDL_FRect* _Rect, SDL_Texture* _texture)
	{
		Rect = _Rect;
		texture = _texture;

		ProximityFuseZone = new SDL_FRect {Rect->x - 20, Rect->y - 20, Rect->w + 40.0f, Rect->h + 40.0f};
	}

void Rocket::Launch()
	{
		if ((!active) && (cooldown <= 0.0f))
			{	
				Rect->x = player->hitbox->x + 27.5f;
				Rect->y = player->hitbox->y;
				ProximityFuseZone->x = Rect->x - 20;
				ProximityFuseZone->y = Rect->y - 20;

				active = true;
			}
	}


Player::Player(SDL_FRect* _hitbox, SDL_Texture* _texture)
	{
		hitbox = _hitbox;
		texture = _texture;

		HP = DEFAULT_PLAYER_HP;
	}	

void Player::Fire()
	{
		if (cooldown <= 0)
			{
				SpawnBullet(PLAYER);
				cooldown = (!GatlingUpgraded) ? DEFAULT_GUN_COOLDOWN : DEFAULT_GUN_COOLDOWN / 5;
			}
		else
			{
				cooldown -= DELTA_TIME;
			}
		
	}

Enemy::Enemy(SDL_FRect* _hitbox, SDL_Texture* _texture)
	{
		hitbox = _hitbox;
		texture = _texture;
	}

void Enemy::Fire()
	{
		if (gunCooldown <= 0)
			{
				SpawnBullet(ENEMY);
				gunCooldown = DEFAULT_ENEMY_GUN_COOLDOWN;
			}
		else
			{
				gunCooldown -= DELTA_TIME;
			}
	}

void Enemy::Move(float velocity)
	{	
		if (destination == NULL && !inMovementCooldown)
			{
				destination = RNG(328.0f, 1277.0f);
			}
		else if (destination != NULL)
			{
				if (Direction == UNKNOWN)
					{
						if ((destination-hitbox->x) > 0)
							{
								Direction = RIGHT;
							}
						else if ((destination - hitbox->x) < 0)
							{
								Direction = LEFT;
							}
					}
				else if (Direction == LEFT)
					{
						if ((hitbox->x - velocity) < destination)
							{
								destination = NULL;
								inMovementCooldown = true;
								movementCooldown = DEFAULT_ENEMY_MOVEMENT_COOLDOWN;
								Direction = UNKNOWN;
								return;
							}
						else 
							{
								hitbox->x -= velocity;
							}
						
					}
				else if (Direction == RIGHT)
					{
						if ((hitbox->x + velocity) > destination)
							{
								destination = NULL;
								inMovementCooldown = true;
								movementCooldown = DEFAULT_ENEMY_MOVEMENT_COOLDOWN;
								Direction = UNKNOWN;
								return;
							}
						else 
							{
								hitbox->x += velocity;
							}
					}

			}
		else if (inMovementCooldown)
			{
				if (movementCooldown <= 0)
					{
						inMovementCooldown = false;
					}
				else 
					{
						movementCooldown -= DELTA_TIME;
					}
			}		
	}




