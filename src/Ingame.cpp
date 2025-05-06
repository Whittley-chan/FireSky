#include "Ingame.h"

bool Paused = false;
bool Loaded = false;

int currentWave = 1;
int enemiesDestroyed = 0;

float timeSinceLastWave = 0;

bool EnemyCanRespawn = true;
float EnemyRespawnCooldown = 5000.0f;
float timeSinceLastRespawn = 0;

BGR IngameBackground = BGR(new SDL_FRect{ 
	(float)wWidth / 2 - 512,
	(float)-(5120  - wHeight),
	(float)1024, 
	(float)5120}, 
	nullptr
);
BGR UpgradeBackground = BGR(new SDL_FRect{
	0,
	0,
	(float)328, 
	(float)wHeight}, 
	nullptr
);
BGR HUDBackground = BGR(new SDL_FRect{
	(float)1352.0f,
	0.0f,
	(float)328, 
	(float)wHeight}, 
	nullptr);
//Button PauseMenu;

Player* player = new Player(new SDL_FRect{ 
	(float)815,
	(float)840,
	(float)50, 
	(float)50}, 
	nullptr
); 

std::vector<Bullet*> PlayerBulletPool; 
std::vector<Bullet*> EnemyBulletPool;
std::vector<Enemy*> EnemyPool;


void IngameMouseHandler(SDL_Event* event)
	{
		if (event->button.button==SDL_BUTTON_LEFT)
			{
				//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Ingame Clicked", appstate->window);
			}
	}

void IngameKeyboardHandler(SDL_Event* event)
	{
		switch (event->key.key)
			{
				case SDLK_A:
					{
						player->isMoving = true;
						player->Direction = LEFT;
						break;
					}
				case SDLK_D:
					{
						player->isMoving = true;
						player->Direction = RIGHT;
						break;
					}
			}

	}

void Load()
	{
		IngameBackground.BGRImg = LoadIMG("./resources/Ingame/Background_Ingame.png");
		UpgradeBackground.BGRImg = LoadIMG("./resources/Ingame/Background_UpgradeMenu.png");
		HUDBackground.BGRImg = LoadIMG("./resources/Ingame/Background_UpgradeMenu.png");
		player->texture = LoadIMG("./resources/Player.png");


		for (int i = 1; i <= MAX_BULLET_NUM; i++)
			{
				Bullet* b = new Bullet(new SDL_FRect{ 
				(float)player->hitbox->x + 25,
				(float)player->hitbox->y,
				(float)4, 
				(float)16}, 
				LoadIMG("./resources/Bullet.png"));
				PlayerBulletPool.push_back(b);
			}
		
		for (int i = 1; i <= MAX_ENEMY_BULLET_NUM; i++)
			{
				Bullet* b = new Bullet(
				new SDL_FRect
				{ 
				(float)player->hitbox->x + 25,
				(float)player->hitbox->y,
				(float)10, 
				(float)19
				}, 
				LoadIMG("./resources/Enemy_Bullet.png"));
				EnemyBulletPool.push_back(b);
			}

		for (int i = 1; i <= MAX_ENEMY_NUM; i++)
			{
				Enemy* e = new Enemy(
				new SDL_FRect 
				{RNG(336.0f, 1344.0f), RNG(0.0f, 200.0f), 50.0f, 50.0f}, LoadIMG("./resources/Enemy_1.png"));
				e->active = true;
				EnemyPool.push_back(e);
			}		

		Loaded = true;
	};


void IngameRender()
	{
		if (!Loaded)
			{
				Load();
			}
		
		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, IngameBackground.BGRImg, NULL, IngameBackground.BGRect);
		SDL_RenderTexture(as->renderer, UpgradeBackground.BGRImg, NULL, UpgradeBackground.BGRect);
		SDL_RenderTexture(as->renderer, UpgradeBackground.BGRImg, NULL, HUDBackground.BGRect);
		SDL_RenderTexture(as->renderer, player->texture, NULL, player->hitbox);
		
		for (Enemy*& e:EnemyPool)
			{
				if (e->active)
					{
						SDL_RenderTexture(as->renderer, e->texture, NULL, e->hitbox);
					}
			}
		for (Bullet* &b: PlayerBulletPool)
			{
				if (b->active)
					{
						SDL_RenderTexture(as->renderer, b->texture, NULL, b->hitbox);
					}
			}

		for (Bullet* &b: EnemyBulletPool)
			{
				if (b->active)
					{
						SDL_RenderTexture(as->renderer, b->texture, NULL, b->hitbox);
					}
				
			}

		if (!Paused)
			{
				Update();
			}
	}

void UpdateEntity(Target target)
	{
		
		if (player->isMoving)
			{
				switch (player->Direction)
					{
						case LEFT:
							{
								player->Move(-(PLR_VELOCITY*DELTA_TIME/1000));
								player->isMoving = false;
								break;
							}
						case RIGHT:
							{
								player->Move(PLR_VELOCITY * DELTA_TIME / 1000);
								player->isMoving = false;
								break;
							}
					}
			}

		timeSinceLastRespawn += DELTA_TIME;
		if ((currentWave * 8)-enemiesDestroyed < MAX_ENEMY_NUM)
			EnemyCanRespawn = false;

		for (Enemy* &e: EnemyPool)
			{
				if (e->active)
					{	
						switch ((e->HP<=0))
							{
								case true:
									{
										enemiesDestroyed++;
										e->active = false;
										e->HP = DEFAULT_ENEMY_HP;
										e->hitbox->x = RNG(336.0f, 1344.0f);
										e->hitbox->y = RNG(0.0f, 250.0f);
										SDL_RenderTexture(as->renderer, NULL, NULL, e->hitbox);
										break;
									}
								case false:
									{
										e->Move(ENM_VELOCITY * DELTA_TIME / 1000);
										break;
									}
							}
						
					}
				else if (!e->active)
					{
						if (EnemyCanRespawn)
							{
								if (timeSinceLastRespawn >= 3500.0f)
									{
										e->active = true;
										EnemyCanRespawn = false;
										EnemyRespawnCooldown = 5000.0f;
										timeSinceLastRespawn = 0.0f;
									}
							}
						else
							{
								if (EnemyRespawnCooldown <= 0)
									{
										EnemyCanRespawn = true;
										EnemyRespawnCooldown = 5000.0f;
									}
								else
									{
										EnemyRespawnCooldown -= DELTA_TIME;
									}
							}
					}
			}
		
	}


void SpawnBullet(Target target)
	{
		switch (target)
			{
				case PLAYER:
					{
						for (Bullet* &b: PlayerBulletPool)
							{
								if (!(b->active))
									{
										b->hitbox->x = player->hitbox->x + 25;
										b->hitbox->y = player->hitbox->y - 15;
										b->active = true;
										return;
									}
								else
									{
										continue;
									}
							}
						break;
					}
				case ENEMY:
					{
						for (Enemy* &e: EnemyPool)
							{
								if (!e->active)
									continue;
								if (e->gunCooldown <= 0)
									{
										for (Bullet* &b: EnemyBulletPool)
											{
												if (!(b->active))
													{
														b->hitbox->x = e->hitbox->x + 25;
														b->hitbox->y = e->hitbox->y + 75;
														b->active = true;
														e->gunCooldown = DEFAULT_ENEMY_GUN_COOLDOWN;
														break;
													}
												else
													{
														continue;
													}
											}
									}
								else 
									{
										e->gunCooldown -= DELTA_TIME;	
									}
								
							}
						break;
					}
				default:
					{
						break;
					}
			}
		
	}

void UpdateBullet(Target target)
	{
		switch (target)
			{
				case PLAYER:
					{
						for (Bullet* &b: PlayerBulletPool)
							{
								if (b->active)
									{
										if (b->hitbox->y < -16)
											{
												b->active = false;
											}
										else
											{
												b->hitbox->y -= DEFAULT_PROJECTILE_VELOCITY;
											}
									}
							}
						break;
					}
				case ENEMY:
					{
						for (Bullet* &b: EnemyBulletPool)
							{
								if (b->active)
									{	
										if (b->hitbox->y > 1352.0f || b->hitbox->x < 328.0f || b->hitbox->x > 1352.0f)
											{
												b->active = false;
												b->headingX = NULL;
												b->headingY = NULL;
											}
										else if ((b->headingX == NULL) && (b->headingY == NULL))
											{
												float _a = player->hitbox->x - b->hitbox->x;
												float _b = player->hitbox->y - b->hitbox->y;
												float _c = std::sqrt(_a * _a + _b * _b);

												b->headingX = _a / _c;
												b->headingY = _b / _c;
											}
										else 
											{
												b->hitbox->x += (DEFAULT_PROJECTILE_VELOCITY / 2 * b->headingX);
												b->hitbox->y += (DEFAULT_PROJECTILE_VELOCITY / 2 * b->headingY) ;
											}
										
									}

							}
						break;
						
					}

				
			}
	}


void CollisionCheck(Target target)
	{
		switch (target)
			{
				case PLAYER:
					{ 
						for (Bullet* &b: PlayerBulletPool)
							{
								for (Enemy* &e: EnemyPool)
									{
										if (b->active)
											{
												if (SDL_HasRectIntersectionFloat(b->hitbox, e->hitbox))
													{
														e->HP -= b->Damage;
														b->active = false;
														std::cout << "HP:" << e->HP << "\n";
													}
											}
									}
							}
						break;
					}
				case ENEMY:
					{
						for (Bullet* &b: EnemyBulletPool)
							{
								if (b->active)
									{
										if (SDL_HasRectIntersectionFloat(b->hitbox, player->hitbox))
											{
												player->HP -= b->Damage;

												b->active = false;
												b->headingX = NULL;
												b->headingY = NULL;

												std::cout << "ENEMY HP:" << player->HP << "\n";
											}
									}
							}
						break;
					}
			}
		
	}


void Update()
	{		
		CollisionCheck(PLAYER);
		CollisionCheck(ENEMY);

		UpdateBullet(PLAYER);
		UpdateBullet(ENEMY);
		
		UpdateEntity(ENEMY);
		SpawnBullet(ENEMY);

		player->Fire();

		if (enemiesDestroyed == currentWave * 8)
			{
				currentWave++;
			}

		IngameBackground.BGRect->y += 0.625;
	}

