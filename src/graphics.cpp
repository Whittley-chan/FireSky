#include "graphics.h"

constexpr char* Title = "FireSky v.0.0.142";

BGR::Background(SDL_FRect* _rect, SDL_Texture* _text)
	{
	    BGRect = _rect;
	    BGRImg = _text;
	}

Button::Button(SDL_FRect* _rect, SDL_Texture* _text)
	{
		ButtonRect = _rect;
		ButtonTexture = _text;
	}
UI::UI_Element(SDL_FRect* _rect, SDL_Texture* _text)
	{
		Rect = _rect;
		Text = _text;
	}

SDL_Texture* LoadIMG(const char* path)
    {
	    SDL_Surface* surface = IMG_Load(path);
		if (!surface)
		    {
		        SDL_Log("Error creating surface: %s", SDL_GetError());
		        return nullptr;
		    }

		SDL_Texture* texture = SDL_CreateTextureFromSurface(as->renderer, surface);
	    SDL_DestroySurface(surface);
		surface = nullptr;

	    if (!texture)
		    {
		        SDL_Log("Error creating texture: %s", SDL_GetError());
		        return nullptr;
		    }
	    return texture;
    }



SDL_AppResult Init()
	{
        as->window = SDL_CreateWindow(Title, wWidth, wHeight, NULL);
        as->renderer = SDL_CreateRenderer(as->window, NULL);
		as->Context = MAIN_MENU;



        if (!as->window || !as->renderer) 
            {
                SDL_Log("Error creating window: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
			{
				SDL_Log("Error initializing component: %s", SDL_GetError());
				return SDL_APP_FAILURE;
			}
		if (!TTF_Init())
			{
				SDL_Log("Error initializing SDL_TTF: %s", SDL_GetError());
				return SDL_APP_FAILURE;
			}


        return SDL_APP_CONTINUE;
	}

