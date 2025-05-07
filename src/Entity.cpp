<<<<<<< HEAD
#include "Entity.h"

Bullet::Bullet(SDL_FRect* _hitbox, SDL_Texture* _texture)
	{
		hitbox = _hitbox;
		texture = _texture;
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
				cooldown = DEFAULT_GUN_COOLDOWN;
			}
		else
			{
				cooldown -= DELTA_TIME;
			}
		
	}

void Player::Move(float velocity)
	{
		if ((hitbox->x+velocity) < 324 || (hitbox->x + velocity) > 1302)
			{
				return;
			}
		hitbox->x += velocity;
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
				destination = RNG(328.0f, 1352.0f);
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




=======
#include "Entity.h"

Bullet::Bullet(SDL_FRect* _hitbox, SDL_Texture* _texture)
	{
		hitbox = _hitbox;
		texture = _texture;
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
				cooldown = DEFAULT_GUN_COOLDOWN;
			}
		else
			{
				cooldown -= DELTA_TIME;
			}
		
	}

void Player::Move(float velocity)
	{
		if ((hitbox->x+velocity) < 324 || (hitbox->x + velocity) > 1302)
			{
				return;
			}
		hitbox->x += velocity;
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
				destination = RNG(328.0f, 1352.0f);
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




>>>>>>> 8efbb6131e1c3c2e4adf6c29c57f71e25ce283d1
