#include "Elements.h"

SDL_Texture* LoadFont(const char* contents, float size)
	{
		TTF_Font* font = TTF_OpenFont("./resources/Fonts/Pixellari.ttf", size);

		if (!font)
			{
				SDL_Log("Failed to load font: %s", SDL_GetError());
				return nullptr;
			}
		SDL_Surface* surface = TTF_RenderText_Blended(font, contents, strlen(contents), SDL_Color{255, 255, 255, 0});

		if (!surface)
			{
				SDL_Log("Failed to render font: %s", SDL_GetError());
				TTF_CloseFont(font);
				return nullptr;
			}


		SDL_Texture*  fontext = SDL_CreateTextureFromSurface(as->renderer, surface);

		if (!fontext)
			{
				SDL_Log("Failed to render font: %s", SDL_GetError());
				SDL_DestroySurface(surface);
				TTF_CloseFont(font);
				return nullptr;
			}
		SDL_DestroySurface(surface);
		surface = nullptr;
		TTF_CloseFont(font);
		return fontext;
	}

SDL_FRect* ScoreboardRect = new SDL_FRect {(float)wWidth - 312, (float)wHeight - 32, 200.0f, 25.0f};
SDL_FRect* WaveBoardRect = new SDL_FRect {(float)wWidth - 312, (float)wHeight - 64, 200.0f, 25.0f};
SDL_FRect* HPRect = new SDL_FRect {(float)wWidth - 312, (float)wHeight - 96, 200.0f, 25.0f};
SDL_FRect* PauseButtonRect = new SDL_FRect {(float)wWidth -50, 0.0f, 50.0f, 50.0f};
SDL_FRect* PauseMenuRect = new SDL_FRect {(float)wWidth/2-300, (float)wHeight/2 - 300, 600.0f, 600.0f};
SDL_FRect* ResumeButtonRect = new SDL_FRect{(float)wWidth/2-150, (float)wHeight/2-100, 300, 100};
SDL_FRect* PauseQuitButtonRect = new SDL_FRect{(float)wWidth/2-150, (float)wHeight/2 + 25, 300, 100};
SDL_FRect* MainMenuBackgroundRect = new SDL_FRect {0.0f, 0.0f, (float)wWidth, (float)wHeight};
SDL_FRect* PlayButtonRect = new SDL_FRect{(float)wWidth/2-150, (float)wHeight/2+100, 300, 100};
SDL_FRect* QuitButtonRect = new SDL_FRect{(float)wWidth/2-150, (float)wHeight/2+205, 300, 100};
SDL_FRect* GameOverBackgroundRect = new SDL_FRect {0.0f, 0.0f, (float)wWidth, (float)wHeight};
SDL_FRect* RestartButtonRect = new SDL_FRect{(float)wWidth/ 2 - 150, 450.0f, 300, 100};
SDL_FRect* GameOverQuitButtonRect = new SDL_FRect{(float)wWidth/ 2 - 100, 550.0f, 200, 100};
SDL_FRect* GameOverTitleRect = new SDL_FRect {(float)wWidth/2-300, 50.0f, 600.0f, 150.0f};
SDL_FRect* FinalScoreRect = new SDL_FRect {(float)wWidth/2-500, 200.0f, 1000.0f, 100.0f};
SDL_FRect* UpgradeMenuTitleRect = new SDL_FRect {14.0f , 400.0f, 300.0f, 50.0f};
SDL_FRect* UpgradeButtonGatlingRect = new SDL_FRect {14.0f , 455.0f, 300.0f, 50.0f};
SDL_FRect* UpgradeButtonRocketRect = new SDL_FRect {14.0f , 510.0f, 300.0f, 50.0f};

SDL_FRect* LeaderboardRect = new SDL_FRect {(float)wWidth - 305, (float)wHeight - 600, 275.0f, 50.0f};
SDL_FRect* HighscoreRect = new SDL_FRect {(float)wWidth - 305, (float)wHeight - 550, 275.0f, 50.0f};