#include "Ingame.h"

static constexpr float dv = PLR_VELOCITY / 1000 * DELTA_TIME;

bool Paused = false;
bool Loaded = false;
bool Ended = false;

int currentWave = 1;
int enemiesDestroyed = 0;
int enemiesDestroyedThisWave = 0;
unsigned long int Score = 0;

float timeSinceLastWave = 0;

bool EnemyCanRespawn = true;
float EnemyRespawnCooldown = 1800.0f;
float timeSinceLastRespawn = 0;

std::vector<Bullet*> PlayerBulletPool; 
std::vector<Bullet*> EnemyBulletPool;
std::vector<Enemy*> EnemyPool;
std::vector<UI*> Leaderboard;
std::vector<unsigned long int> Highscores;


SDL_Texture* Explosion = nullptr;

BGR* IngameBackground1 = new BGR(new SDL_FRect{ 
	(float)wWidth / 2 - 512,
	(float)-(8192  - wHeight),
	(float)1024, 
	(float)8192}, 
	nullptr
);

BGR* IngameBackground2 = new BGR(new SDL_FRect{ 
	(float)wWidth / 2 - 512,
	(float)IngameBackground1->BGRect->y - 8192,
	(float)1024, 
	(float)8192}, 
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
UI* LeaderboardTitle = new UI(LeaderboardRect, nullptr);
UI* Wave = new UI(WaveBoardRect, nullptr);
UI* HP = new UI(HPRect, nullptr);
UI* UpgradeMenuTitle = new UI(UpgradeMenuTitleRect, nullptr);
Button* UpgradeButtonGatling = new Button(UpgradeButtonGatlingRect, nullptr);
Button* UpgradeButtonRocket = new Button(UpgradeButtonRocketRect, nullptr);


Button* PauseButton = new Button(PauseButtonRect, nullptr);


Player* player = new Player(new SDL_FRect{ 
	(float)815,
	(float)840,
	(float)75, 
	(float)75}, 
	nullptr
); 

RKT* rocket = new RKT(new SDL_FRect{player->hitbox->x + 27.5f, player->hitbox->y - 15, 20.0f, 42.0f}, nullptr);



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
						finalScore = Score;

						auto i = Highscores.begin();
						while (i != Highscores.end() && *i > Score) 
							{
								i++;
							}
						Highscores.insert(i, Score);
						Highscores.pop_back();

						Score = 0;

						for (int i = MAX_ENEMY_BULLET_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(EnemyBulletPool[i]->texture);
								EnemyBulletPool[i]->texture = nullptr;
								delete EnemyBulletPool[i]->hitbox;
								EnemyBulletPool[i]->hitbox = nullptr;
								delete EnemyBulletPool[i];
								EnemyBulletPool[i] = nullptr;
								EnemyBulletPool.pop_back();
							}

						for (int i = MAX_BULLET_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(PlayerBulletPool[i]->texture);
								PlayerBulletPool[i]->texture = nullptr;
								delete PlayerBulletPool[i]->hitbox;
								PlayerBulletPool[i]->hitbox = nullptr;
								delete PlayerBulletPool[i];
								PlayerBulletPool[i] = nullptr;
								PlayerBulletPool.pop_back();
							}

						for (int i = MAX_ENEMY_NUM - 1; i >=0; i--)
							{
								SDL_DestroyTexture(EnemyPool[i]->texture);
								EnemyPool[i]->texture = nullptr;
								delete EnemyPool[i]->hitbox;
								EnemyPool[i]->hitbox = nullptr;
								delete EnemyPool[i];
								EnemyPool[i] = nullptr;
								EnemyPool.pop_back();
							}

						for (int i = 4; i >= 0; i--)
							{
								SDL_DestroyTexture(Leaderboard[i]->Text);
								Leaderboard[i]->Text = nullptr;
								delete Leaderboard[i]->Rect;
								Leaderboard[i]->Rect = nullptr;
								delete Leaderboard[i];
								Leaderboard[i] = nullptr;
								Leaderboard.pop_back();

							}

						SDL_DestroyTexture(IngameBackground1->BGRImg);
						SDL_DestroyTexture(IngameBackground2->BGRImg);
						SDL_DestroyTexture(HUDBackground->BGRImg);
						SDL_DestroyTexture(UpgradeBackground->BGRImg);
						SDL_DestroyTexture(PauseButton->ButtonTexture);
						SDL_DestroyTexture(UpgradeButtonGatling->ButtonTexture);
						SDL_DestroyTexture(UpgradeButtonRocket->ButtonTexture);
						SDL_DestroyTexture(Explosion);
						SDL_DestroyTexture(Scoreboard->Text);
						SDL_DestroyTexture(LeaderboardTitle->Text);
						SDL_DestroyTexture(Wave->Text);
						SDL_DestroyTexture(HP->Text);
						SDL_DestroyTexture(player->texture);
						SDL_DestroyTexture(rocket->texture);

						IngameBackground1->BGRImg = nullptr;
						IngameBackground2->BGRImg = nullptr;
						HUDBackground->BGRImg = nullptr;
						UpgradeBackground->BGRImg = nullptr;
						PauseButton->ButtonTexture = nullptr;
						UpgradeButtonGatling->ButtonTexture = nullptr;
						UpgradeButtonRocket->ButtonTexture = nullptr;
						player->texture = nullptr;
						Explosion = nullptr;
						Scoreboard->Text = nullptr;
						LeaderboardTitle->Text = nullptr;
						Wave->Text = nullptr;
						HP->Text = nullptr;
						rocket->texture = nullptr;

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
		else if (event->button.x>=UpgradeButtonGatling->ButtonRect->x
			&&event->button.x<=UpgradeButtonGatling->ButtonRect->x+UpgradeButtonGatling->ButtonRect->w
			&&event->button.y>=UpgradeButtonGatling->ButtonRect->y
			&&event->button.y<=UpgradeButtonGatling->ButtonRect->y+UpgradeButtonGatling->ButtonRect->h)
				{
					if (Score > 150)
						{
							SDL_DestroyTexture(UpgradeButtonGatling->ButtonTexture);
							UpgradeButtonGatling->ButtonTexture = LoadFont("Gatling: Upgraded", 54);

							player->GatlingUpgraded = true;
						}
				}
		else if (event->button.x>=UpgradeButtonRocket->ButtonRect->x
			&&event->button.x<=UpgradeButtonRocket->ButtonRect->x+UpgradeButtonRocket->ButtonRect->w
			&&event->button.y>=UpgradeButtonRocket->ButtonRect->y
			&&event->button.y<=UpgradeButtonRocket->ButtonRect->y+UpgradeButtonRocket->ButtonRect->h)
				{
					if (Score > 1500)
						{
							SDL_DestroyTexture(UpgradeButtonRocket->ButtonTexture);
							UpgradeButtonRocket->ButtonTexture = LoadFont("Rocket: Upgraded", 54);

							player->RocketUpgraded = true;
						}
				}
		
	}

void IngameKeyboardHandler()
	{
		if (Keyboard == nullptr) return;
		if (Keyboard[SDL_SCANCODE_W] && !(player->hitbox->y-dv<=0)) player->hitbox->y -= dv;
		if (Keyboard[SDL_SCANCODE_A] && !(player->hitbox->x - dv <= 328)) player->hitbox->x -= dv;
		if (Keyboard[SDL_SCANCODE_S] && !(player->hitbox->y + dv >= wHeight - 75)) player->hitbox->y += dv;
		if (Keyboard[SDL_SCANCODE_D] && !(player->hitbox->x + dv >= 1277)) player->hitbox->x += dv;
		if (Keyboard[SDL_SCANCODE_F]) rocket->Launch();
	}

void Load()
	{
		
		std::ifstream file("./resources/Highscores.txt");
		if (!file)
			{
				changeState(QUIT);
			}

		unsigned long int a;
		while (file >> a && Highscores.size() < 5) 
			{
				Highscores.push_back(a);
			}

		file.close();
		
		currentWave = 1;
		enemiesDestroyed = 0;
		enemiesDestroyedThisWave = 0;
		Score = 0;
		player->HP = DEFAULT_PLAYER_HP;

		timeSinceLastWave = 0;

		EnemyCanRespawn = true;
		EnemyRespawnCooldown = 1800.0f;
		timeSinceLastRespawn = 0;

		
		IngameBackground1->BGRImg = LoadIMG("./resources/Background/Ingame_1.png");
		IngameBackground2->BGRImg = LoadIMG("./resources/Background/Ingame_2.png");
		UpgradeBackground->BGRImg = LoadIMG("./resources/Background/UpgradeMenu.png");
		HUDBackground->BGRImg = LoadIMG("./resources/Background/HUD_1.png");
		UpgradeMenuTitle->Text = LoadFont("UPGRADE", 54);
		LeaderboardTitle->Text = LoadFont("LEADERBOARD", 54);
		UpgradeButtonGatling->ButtonTexture = LoadFont("Gatling: 150", 54);
		UpgradeButtonRocket->ButtonTexture = LoadFont("Rocket: 1500", 54);

		PauseButton->ButtonTexture = LoadIMG("./resources/Button/PauseButton.png");
		player->texture = LoadIMG("./resources/Entity/Player.png");
		Explosion = LoadIMG("./resources/explosion.png");
		Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 54);
		Wave->Text = LoadFont(((std::string)"Wave: " + std::to_string(currentWave)).c_str(), 54);
		HP->Text = LoadFont(((std::string)"HP: " + std::to_string((int)player->HP)).c_str(), 54);
		

		for (int i = 0; i < 5; i++)
			{	
				std::ostringstream oss;
				unsigned long int a = Highscores[i];
				oss << std::setfill('0') << std::setw(10) << a;
				std::string st = oss.str();

				UI* s = new UI(new SDL_FRect{
				HighscoreRect->x,
				HighscoreRect->y + (i*55),
				HighscoreRect->w,
				HighscoreRect->h},
				LoadFont(st.c_str(), 54)
				);
				Leaderboard.push_back(s);
			}

		for (int i = 1; i <= MAX_BULLET_NUM; i++)
			{
				Bullet* b = new Bullet(new SDL_FRect{ 
				(float)player->hitbox->x + 25,
				(float)player->hitbox->y,
				(float)4, 
				(float)16}, 
				LoadIMG("./resources/Munitions/Bullet.png"));
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
				LoadIMG("./resources/Munitions/Enemy_Bullet.png"));
				EnemyBulletPool.push_back(b);
			}


		for (int i = 1; i <= MAX_ENEMY_NUM; i++)
			{
				Enemy* e = new Enemy(
				new SDL_FRect 
					{ RNG(336.0f, 1344.0f), RNG(0.0f, 200.0f), 75.0f, 75.0f }, LoadIMG((((std::string)"./resources/Entity/Enemy_")+std::to_string(RNG(1, 3))+((std::string)".png")).c_str()));
				e->active = true;
				EnemyPool.push_back(e);
			}
		

		rocket->texture = LoadIMG("./resources/Munitions/Rocket.png");

		player->HP = DEFAULT_PLAYER_HP;
		player->hitbox->x = 815.0f;
		player->hitbox->y = 840.0f;
		player->GatlingUpgraded = false;
		player->RocketUpgraded = false;

		Loaded = true;
	};


void IngameRender()
	{
		if (Ended) return;
		
		if (!Loaded)
			{
				Load();
			}
		

		SDL_RenderClear(as->renderer);
		SDL_RenderTexture(as->renderer, IngameBackground1->BGRImg, NULL, IngameBackground1->BGRect);
		SDL_RenderTexture(as->renderer, IngameBackground2->BGRImg, NULL, IngameBackground2->BGRect);
		SDL_RenderTexture(as->renderer, UpgradeBackground->BGRImg, NULL, UpgradeBackground->BGRect);
		SDL_RenderTexture(as->renderer, HUDBackground->BGRImg, NULL, HUDBackground->BGRect);
		SDL_RenderTexture(as->renderer, Scoreboard->Text, NULL, Scoreboard->Rect);
		SDL_RenderTexture(as->renderer, LeaderboardTitle->Text, NULL, LeaderboardTitle->Rect);
		SDL_RenderTexture(as->renderer, Wave->Text, NULL, Wave->Rect);
		SDL_RenderTexture(as->renderer, HP->Text, NULL, HP->Rect);
		

		SDL_RenderTexture(as->renderer, UpgradeMenuTitle->Text, NULL, UpgradeMenuTitle->Rect);
		SDL_RenderTexture(as->renderer, UpgradeButtonGatling->ButtonTexture, NULL, UpgradeButtonGatling->ButtonRect);
		SDL_RenderTexture(as->renderer, UpgradeButtonRocket->ButtonTexture, NULL, UpgradeButtonRocket->ButtonRect);
		SDL_RenderTexture(as->renderer, PauseButton->ButtonTexture, NULL, PauseButton->ButtonRect);
		SDL_RenderTexture(as->renderer, player->texture, NULL, player->hitbox);
		

		for (UI* &u: Leaderboard)
			{
				SDL_RenderTexture(as->renderer, u->Text, NULL, u->Rect);
			}
		if (!Paused)
			{
				Update();
				
				if (rocket->active) 
					{
						SDL_RenderTexture(as->renderer, rocket->texture, NULL, rocket->Rect);
					}

				for (Enemy* &e:EnemyPool)
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
								SDL_RenderTextureRotated(as->renderer, b->texture, NULL, b->hitbox, asinf(b->headingX), NULL, SDL_FLIP_NONE);
							}
				
					}

			}
	}

void UpdateEntity(Target target)
	{	
		if (player->HP <= 0)
			{
				changeState(GAME_OVER);
				return;
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
										Score += currentWave * 10;

										SDL_RenderTexture(as->renderer, Explosion, NULL, e->hitbox);
										SDL_DestroyTexture(Scoreboard->Text);
										Scoreboard->Text = LoadFont(((std::string)"Score: " + std::to_string(Score)).c_str(), 54);

										e->HP = DEFAULT_ENEMY_HP + currentWave * 35;
										
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
						if (rocket->active)
							{
								if (rocket->Rect->y < 0) 
									{
										rocket->active = false;
										rocket->Rect->x = player->hitbox->x + 27.5f;
										rocket->Rect->y = player->hitbox->y;

										if (player->RocketUpgraded)
											rocket->cooldown = DEFAULT_ROCKET_COOLDOWN / 4;
										else
											rocket->cooldown = DEFAULT_ROCKET_COOLDOWN;
									}
									
								else
									{
										rocket->Rect->y -= DEFAULT_ROCKET_VELOCITY;
										rocket->ProximityFuseZone->y = rocket->Rect->y - 10;
									}
							}
						else if (!rocket->active && rocket->cooldown > 0)
							{
								
								rocket->cooldown -= DELTA_TIME;
							}


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
												b->hitbox->y -= DEFAULT_BULLET_VELOCITY;
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
												b->hitbox->x += (DEFAULT_BULLET_VELOCITY / 2 * b->headingX);
												b->hitbox->y += (DEFAULT_BULLET_VELOCITY / 2 * b->headingY) ;
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
						if (rocket->active)
							{
								bool hit = false;
								for (Enemy* &e: EnemyPool)
										{
											if (e->active)
												{
													if (SDL_HasRectIntersectionFloat(rocket->ProximityFuseZone, e->hitbox))
														{
															e->HP -= rocket->Damage;
															hit = true;
														}
												}
											
										}
								if (hit)
									{
										rocket->active = false;
										
										if (player->RocketUpgraded)
											rocket->cooldown = DEFAULT_ROCKET_COOLDOWN / 4;
										else
											rocket->cooldown = DEFAULT_ROCKET_COOLDOWN;
									}
								
							}
						for (Bullet* &b: PlayerBulletPool)
							{
								for (Enemy* &e: EnemyPool)
									{
										if (b->active && e->active)
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
												SDL_DestroyTexture(HP->Text);
												HP->Text = LoadFont(((std::string)"HP: " + std::to_string((int)player->HP)).c_str(), 54);

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
		UpdateEntity(ENEMY);
		CollisionCheck(PLAYER);
		CollisionCheck(ENEMY);

		UpdateBullet(PLAYER);
		UpdateBullet(ENEMY);
		
		
		SpawnBullet(ENEMY);

		player->Fire();

		if (enemiesDestroyedThisWave == currentWave * 8)
			{
				player->HP = DEFAULT_PLAYER_HP + currentWave * 50;
				currentWave++;
				SDL_DestroyTexture(Wave->Text);
				Wave->Text = LoadFont(((std::string)"Wave: " + std::to_string(currentWave)).c_str(), 54);
				enemiesDestroyedThisWave = 0;
			}

		IngameBackground1->BGRect->y += 0.425f;
		IngameBackground2->BGRect->y += 0.425f;

		if (IngameBackground1->BGRect->y > float(wWidth))
			{
				IngameBackground1->BGRect->y = IngameBackground2->BGRect->y - 8192.0f;
			}
		else if (IngameBackground2->BGRect->y > float(wWidth))
			{
				IngameBackground2->BGRect->y = IngameBackground1->BGRect->y - 8192.0f;
			}
	}



