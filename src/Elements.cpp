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
				return nullptr;
			}
		SDL_Texture*  fontext = SDL_CreateTextureFromSurface(as->renderer, surface);
		if (!fontext)
			{
				SDL_Log("Failed to render font: %s", SDL_GetError());
				return nullptr;
			}
		SDL_DestroySurface(surface);
		return fontext;
	}

SDL_FRect* ScoreboardRect = new SDL_FRect {1368.0f, 993.0f, 200.0f, 25.0f};
SDL_FRect* PauseButtonRect = new SDL_FRect {1580.0f, 0.0f, 100.0f, 100.0f};
SDL_FRect* PauseMenuRect = new SDL_FRect {328.0f, 237.0f, 1024.0f, 576.0f};
SDL_FRect* ResumeButtonRect = new SDL_FRect{(float)wWidth/2-125, (float)wHeight/2-100, 200, 100};
SDL_FRect* PauseQuitButtonRect = new SDL_FRect{(float)wWidth/2-125, (float)wHeight/2 + 25, 200, 100};
SDL_FRect* MainMenuBackgroundRect = new SDL_FRect {0.0f, 0.0f, (float)wWidth, (float)wHeight};
SDL_FRect* PlayButtonRect = new SDL_FRect{(float)wWidth/2-125, (float)wHeight/2+100, 200, 100};
SDL_FRect* QuitButtonRect = new SDL_FRect{(float)wWidth/2-125, (float)wHeight/2+205, 200, 100};
SDL_FRect* GameOverBackgroundRect = new SDL_FRect {0.0f, 0.0f, (float)wWidth, (float)wHeight};
SDL_FRect* RestartButtonRect = new SDL_FRect{(float)wWidth/2-125, (float)wHeight/2+205, 200, 100};
SDL_FRect* GameOverTitleRect = new SDL_FRect {(float)wWidth/2-300, 50.0f, 600.0f, 150.0f};
SDL_FRect* FinalScoreRect = new SDL_FRect {(float)wWidth/2-500, 200.0f, 1000.0f, 100.0f};