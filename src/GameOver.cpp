#include <GameOver.h>

static bool Loaded = false;

unsigned long int finalScore = 0;

BGR* GameOverBackground = new BGR(GameOverBackgroundRect, nullptr);
Button* RestartButton = new Button(RestartButtonRect, nullptr);
Button* GameOverQuitButton = new Button(QuitButtonRect, nullptr);
UI* GameOverTitle = new UI(GameOverTitleRect, nullptr);
UI* FinalScore = new UI(FinalScoreRect, nullptr);


void GameOverRender()
	{
		if (!Loaded)
			{
				GameOverBackground->BGRImg = LoadIMG("./resources/Background/GameOver.png");
				GameOverTitle->Text = LoadFont("GAME OVER!", 128);
				FinalScore->Text = LoadFont((((std::string)"Your final score is ") + std::to_string(finalScore)).c_str(), 54);
				
			}

		SDL_RenderTexture(as->renderer, GameOverBackground->BGRImg, NULL, GameOverBackground->BGRect);
		SDL_RenderTexture(as->renderer, GameOverTitle->Text, NULL, GameOverTitle->Rect);
		SDL_RenderTexture(as->renderer, FinalScore->Text, NULL, FinalScore->Rect);
	}
void GameOverMouseHandler()
	{
		
	
	}

