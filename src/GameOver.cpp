#include <GameOver.h>

static bool Loaded = false;

unsigned long int finalScore = 0;

BGR* GameOverBackground = new BGR(GameOverBackgroundRect, nullptr);
Button* RestartButton = new Button(RestartButtonRect, nullptr);
Button* GameOverQuitButton = new Button(GameOverQuitButtonRect, nullptr);
UI* GameOverTitle = new UI(GameOverTitleRect, nullptr);
UI* FinalScore = new UI(FinalScoreRect, nullptr);

static void changeState(GameContext context)
	{
		switch (context)
			{
				case IN_GAME:
					{	
						
						as->Context = IN_GAME;
						Ended = false;
						SDL_DestroyTexture(GameOverBackground->BGRImg);
						SDL_DestroyTexture(GameOverTitle->Text);
						SDL_DestroyTexture(FinalScore->Text);
						SDL_DestroyTexture(RestartButton->ButtonTexture);
						SDL_DestroyTexture(GameOverQuitButton->ButtonTexture);

						GameOverBackground->BGRImg = nullptr;
						GameOverTitle->Text = nullptr;
						FinalScore->Text = nullptr;
						RestartButton->ButtonTexture = nullptr;
						GameOverQuitButton->ButtonTexture = nullptr;


						break;
					}

				case QUIT:	
					{
						
						as->Context = QUIT;
						break;
					}
			}
	}

void GameOverRender()
	{
		if (!Loaded)
			{
				GameOverBackground->BGRImg = LoadIMG("./resources/Background/GameOver.png");
				GameOverTitle->Text = LoadFont("GAME OVER!", 128);
				FinalScore->Text = LoadFont((((std::string)"Your final score is ") + std::to_string(finalScore)).c_str(), 54);
				RestartButton->ButtonTexture = LoadFont("RESTART", 54);
				GameOverQuitButton->ButtonTexture = LoadFont("QUIT", 54);

				Loaded = true;
			}

		SDL_RenderTexture(as->renderer, GameOverBackground->BGRImg, NULL, GameOverBackground->BGRect);
		SDL_RenderTexture(as->renderer, GameOverTitle->Text, NULL, GameOverTitle->Rect);
		SDL_RenderTexture(as->renderer, FinalScore->Text, NULL, FinalScore->Rect);
		SDL_RenderTexture(as->renderer, RestartButton->ButtonTexture, NULL, RestartButton->ButtonRect);
		SDL_RenderTexture(as->renderer, GameOverQuitButton->ButtonTexture, NULL, GameOverQuitButton->ButtonRect);

	}

void GameOverMouseHandler(SDL_Event* event)
	{
		if (event->button.x>=RestartButton->ButtonRect->x
			&&event->button.x<=RestartButton->ButtonRect->x+RestartButton->ButtonRect->w
			&&event->button.y>=RestartButton->ButtonRect->y
			&&event->button.y<=RestartButton->ButtonRect->y+RestartButton->ButtonRect->h)
			{
				Loaded = false;
				changeState(IN_GAME);
			}
		else if (event->button.x >= GameOverQuitButton->ButtonRect->x
			&&event->button.x <= GameOverQuitButton->ButtonRect->x+GameOverQuitButton->ButtonRect->w
			&&event->button.y >= GameOverQuitButton->ButtonRect->y
			&&event->button.y <= GameOverQuitButton->ButtonRect->y+GameOverQuitButton->ButtonRect->h)
			{
				PauseMenuChangeState(QUIT);
				
			}
	
	}

