<<<<<<< HEAD
#include "Ingame.h"

bool Paused = false;
bool Loaded = false;
bool Ended = false;

int currentWave = 1;
int enemiesDestroyed;
int enemiesDestroyedThisWave = 0;
unsigned long int Score = 0;

float timeSinceLastWave = 0;

bool EnemyCanRespawn = true;
float EnemyRespawnCooldown = 1800.0f;
float timeSinceLastRespawn = 0;

SDL_Texture* Explosion = nullptr;

BGR* IngameBackground = new BGR(new SDL_FRect{ 
	(float)wWidth / 2 - 512,
	(float)-(5120  - wHeight),
	(float)1024, 
	(float)5120}, 
	nullptr
);
BGR* UpgradeBackground = new BGR(new SDL_FRect{
	0,
	0,
	(float)328, 
	(float)1050}, 
	nullptr
);
BGR* HUDBackground = new BGR(new SDL_FRect{
	(float)1352.0f,
	0.0f,
	(float)328, 
	(float)1050}, 
	nullptr);

UI* Scoreboard = new UI(ScoreboardRect, nullptr);
Button* PauseButton = new Button(PauseButtonRect, nullptr);


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

static void changeState(GameContext context)
	{
		switch (context) 
			{
				case PAUSED:
					{
						Paused = true;
						as->Context = PAUSED;
						break;
					}
				case GAME_OVER:
					{
						as->Context = GAME_OVER;
						Ended = true;
						for (int i = MAX_ENEMY_BULLET_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(EnemyBulletPool[i]->texture);
								delete EnemyBulletPool[i]->hitbox;
								delete EnemyBulletPool[i];
								EnemyBulletPool.pop_back();
							}

						for (int i = MAX_BULLET_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(PlayerBulletPool[i]->texture);
								delete PlayerBulletPool[i]->hitbox;
								delete PlayerBulletPool[i];
								PlayerBulletPool.pop_back();
							}

						for (int i = MAX_ENEMY_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(EnemyPool[i]->texture);
								delete EnemyPool[i]->hitbox;
								delete EnemyPool[i];
								EnemyPool.pop_back();
							}

						SDL_DestroyTexture(IngameBackground->BGRImg);
						SDL_DestroyTexture(HUDBackground->BGRImg);
						SDL_DestroyTexture(UpgradeBackground->BGRImg);
						SDL_DestroyTexture(player->texture);
						SDL_DestroyTexture(PauseButton->ButtonTexture);
						SDL_DestroyTexture(Explosion);
						SDL_DestroyTexture(Scoreboard->Text);

						delete IngameBackground->BGRect;
						delete HUDBackground->BGRect;
						delete UpgradeBackground->BGRect;
						delete player->hitbox;
						delete PauseButton->ButtonRect;
						
						delete Scoreboard;
						delete IngameBackground;
						delete HUDBackground;
						delete UpgradeBackground;
						delete player;
						delete PauseButton;


						Loaded = false;
						break;
					}
			}
	}

void IngameMouseHandler(SDL_Event* event)
	{
		if (event->button.x>=PauseButton->ButtonRect->x
			&&event->button.x<=PauseButton->ButtonRect->x+PauseButton->ButtonRect->w
			&&event->button.y>=PauseButton->ButtonRect->y
			&&event->button.y<=PauseButton->ButtonRect->y+PauseButton->ButtonRect->h)
			{
				changeState(PAUSED);

			}
	}

void IngameKeyboardHandler()
	{
		if (Keyboard == nullptr) return;
		if (Keyboard[SDL_SCANCODE_W]) player->hitbox->y -= PLR_VELOCITY * DELTA_TIME / 1000;
		if (Keyboard[SDL_SCANCODE_A]) player->hitbox->x -= PLR_VELOCITY * DELTA_TIME / 1000;
		if (Keyboard[SDL_SCANCODE_S]) player->hitbox->y += PLR_VELOCITY * DELTA_TIME / 1000;
		if (Keyboard[SDL_SCANCODE_D]) player->hitbox->x += PLR_VELOCITY * DELTA_TIME / 1000;
		if (Keyboard[SDL_SCANCODE_L]) changeState(GAME_OVER);
	}

void Load()
	{
		currentWave = 1;
		enemiesDestroyed;
		enemiesDestroyedThisWave = 0;
		Score = 0;

		timeSinceLastWave = 0;

		EnemyCanRespawn = true;
		EnemyRespawnCooldown = 1800.0f;
		timeSinceLastRespawn = 0;

		IngameBackground->BGRImg = LoadIMG("./resources/Background/Ingame.png");
		UpgradeBackground->BGRImg = LoadIMG("./resources/Background/UpgradeMenu.png");
		HUDBackground->BGRImg = LoadIMG("./resources/Background/HUD_1.png");
		PauseButton->ButtonTexture = LoadIMG("./resources/Button/PauseButton.png");
		player->texture = LoadIMG("./resources/Player.png");
		Explosion = LoadIMG("./resources/explosion.png");
		Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 14);
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
					{ RNG(336.0f, 1344.0f), RNG(0.0f, 200.0f), 50.0f, 50.0f }, LoadIMG((((std::string)"./resources/Enemy_")+std::to_string(RNG(1, 3))+((std::string)".png")).c_str()));
				e->active = true;
				EnemyPool.push_back(e);
			}		

		Loaded = true;
	};


void IngameRender()
	{
		if (Ended) return;
		
		if (!Loaded)
			{
				Load();
			}

		Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 54);

		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, IngameBackground->BGRImg, NULL, IngameBackground->BGRect);
		SDL_RenderTexture(as->renderer, UpgradeBackground->BGRImg, NULL, UpgradeBackground->BGRect);
		SDL_RenderTexture(as->renderer, HUDBackground->BGRImg, NULL, HUDBackground->BGRect);
		SDL_RenderTexture(as->renderer, Scoreboard->Text, NULL, Scoreboard->Rect);
		SDL_RenderTexture(as->renderer, PauseButton->ButtonTexture, NULL, PauseButton->ButtonRect);
		SDL_RenderTexture(as->renderer, player->texture, NULL, player->hitbox);
		

		if (!Paused)
			{
				Update();
			
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
								player->Move(-(PLR_VELOCITY * DELTA_TIME/1000));
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

		if (timeSinceLastWave < 2.0f)
			{
				timeSinceLastWave += DELTA_TIME;
				return;
			}
		if ((currentWave * 8) - enemiesDestroyedThisWave < MAX_ENEMY_NUM)
			EnemyCanRespawn = false;

		for (Enemy* &e: EnemyPool)
			{
				if (e->active)
					{	
						switch (((e->HP <= 0) ? true : false))
							{
								case true:
									{	
										e->active = false;
										enemiesDestroyed++;
										enemiesDestroyedThisWave++;

										SDL_RenderTexture(as->renderer, Explosion, NULL, e->hitbox);
										e->HP = DEFAULT_ENEMY_HP;
										
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
						SDL_RenderTexture(as->renderer, Explosion, NULL, e->hitbox);
						if (EnemyCanRespawn)
							{
								if (timeSinceLastRespawn >= 1500.0f)
									{	
										SDL_RenderTexture(as->renderer, NULL, NULL, e->hitbox);
										e->hitbox->x = RNG(336.0f, 1344.0f);
										e->hitbox->y = RNG(0.0f, 250.0f);
										e->active = true;
										EnemyCanRespawn = false;
										EnemyRespawnCooldown = 1800.0f;
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
										b->Damage = DEFAULT_PLAYER_DAMAGE;
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
														b->Damage = DEFAULT_ENEMY_DAMAGE;
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

		Score = enemiesDestroyed * 10;

		if (enemiesDestroyedThisWave == currentWave * 8)
			{
				currentWave++;
				enemiesDestroyedThisWave = 0;
			}

		//IngameBackground->BGRect->y += 0.625;
	}



=======
#include "Ingame.h"

bool Paused = false;
bool Loaded = false;

int currentWave = 1;
int enemiesDestroyed;
int enemiesDestroyedThisWave = 0;
unsigned long int Score = 0;

float timeSinceLastWave = 0;

bool EnemyCanRespawn = true;
float EnemyRespawnCooldown = 1800.0f;
float timeSinceLastRespawn = 0;

SDL_Texture* Explosion = nullptr;

BGR* IngameBackground = new BGR(new SDL_FRect{ 
	(float)wWidth / 2 - 512,
	(float)-(5120  - wHeight),
	(float)1024, 
	(float)5120}, 
	nullptr
);
BGR* UpgradeBackground = new BGR(new SDL_FRect{
	0,
	0,
	(float)328, 
	(float)1050}, 
	nullptr
);
BGR* HUDBackground = new BGR(new SDL_FRect{
	(float)1352.0f,
	0.0f,
	(float)328, 
	(float)1050}, 
	nullptr);

UI* Scoreboard = new UI(ScoreboardRect, nullptr);
Button* PauseButton = new Button(PauseButtonRect, nullptr);


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
		if (event->button.x>=PauseButton->ButtonRect->x
			&&event->button.x<=PauseButton->ButtonRect->x+PauseButton->ButtonRect->w
			&&event->button.y>=PauseButton->ButtonRect->y
			&&event->button.y<=PauseButton->ButtonRect->y+PauseButton->ButtonRect->h)
			{
				IngameChangeState(PAUSED);

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
		IngameBackground->BGRImg = LoadIMG("./resources/Background/Ingame.png");
		UpgradeBackground->BGRImg = LoadIMG("./resources/Background/UpgradeMenu.png");
		HUDBackground->BGRImg = LoadIMG("./resources/Background/HUD_1.png");
		PauseButton->ButtonTexture = LoadIMG("./resources/Button/PauseButton.png");
		player->texture = LoadIMG("./resources/Player.png");
		Explosion = LoadIMG("./resources/explosion.png");
		Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 54);

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
					{ RNG(336.0f, 1344.0f), RNG(0.0f, 200.0f), 50.0f, 50.0f }, LoadIMG((((std::string)"./resources/Enemy_")+std::to_string(RNG(1, 3))+((std::string)".png")).c_str()));
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

		Score = enemiesDestroyed * 10;
		
		Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 54);

		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, IngameBackground->BGRImg, NULL, IngameBackground->BGRect);
		SDL_RenderTexture(as->renderer, UpgradeBackground->BGRImg, NULL, UpgradeBackground->BGRect);
		SDL_RenderTexture(as->renderer, HUDBackground->BGRImg, NULL, HUDBackground->BGRect);
		SDL_RenderTexture(as->renderer, Scoreboard->Text, NULL, Scoreboard->Rect);
		SDL_RenderTexture(as->renderer, PauseButton->ButtonTexture, NULL, PauseButton->ButtonRect);
		SDL_RenderTexture(as->renderer, player->texture, NULL, player->hitbox);
		

		if (!Paused)
			{
				Update();
			
		
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
								player->Move(-(PLR_VELOCITY * DELTA_TIME/1000));
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

		if (timeSinceLastWave < 2.0f)
			{
				timeSinceLastWave += DELTA_TIME;
				return;
			}
		if ((currentWave * 8) - enemiesDestroyedThisWave < MAX_ENEMY_NUM)
			EnemyCanRespawn = false;

		for (Enemy* &e: EnemyPool)
			{
				if (e->active)
					{	
						switch (((e->HP <= 0) ? true : false))
							{
								case true:
									{	
										e->active = false;
										enemiesDestroyed++;
										enemiesDestroyedThisWave++;

										SDL_RenderTexture(as->renderer, Explosion, NULL, e->hitbox);
										e->HP = DEFAULT_ENEMY_HP;
										
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
						SDL_RenderTexture(as->renderer, Explosion, NULL, e->hitbox);
						if (EnemyCanRespawn)
							{
								if (timeSinceLastRespawn >= 1500.0f)
									{	
										SDL_RenderTexture(as->renderer, NULL, NULL, e->hitbox);
										e->hitbox->x = RNG(336.0f, 1344.0f);
										e->hitbox->y = RNG(0.0f, 250.0f);
										e->active = true;
										EnemyCanRespawn = false;
										EnemyRespawnCooldown = 1800.0f;
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
										b->Damage = DEFAULT_PLAYER_DAMAGE;
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
														b->Damage = DEFAULT_ENEMY_DAMAGE;
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

		Score = enemiesDestroyed * 10;

		if (enemiesDestroyedThisWave == currentWave * 8)
			{
				currentWave++;
				enemiesDestroyedThisWave = 0;
			}

		//IngameBackground->BGRect->y += 0.625;
	}

void IngameChangeState(GameContext context)
	{
		switch (context) 
			{
				case PAUSED:
					{
						Paused = true;
						as->Context = PAUSED;
						break;
					}
				case GAME_OVER:
					{
						as->Context = GAME_OVER;
						break;
					}
			}
	}

>>>>>>> 8efbb6131e1c3c2e4adf6c29c57f71e25ce283d1
