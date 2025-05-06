#include "graphics.h"


const Uint16			wWidth = 1680;
const Uint16			wHeight = 1050;

const char*             Title = "FireSky v.0.0.142";



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


SDL_Texture* LoadIMG(const char* path)
    {
	    SDL_Surface* surface = new SDL_Surface;
		surface = IMG_Load(path);
		if (!surface)
		    {
		        SDL_Log("Error creating surface: %s", SDL_GetError());
		        return nullptr;
		    }

		SDL_Texture* texture = new SDL_Texture;
		texture	= SDL_CreateTextureFromSurface(as->renderer, surface);
	    SDL_DestroySurface(surface);
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

        if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Lorem ipsum Dolor sit amet", as->window))
            {
                SDL_Log("Error creating debug message: %s", SDL_GetError());
            }
        return SDL_APP_CONTINUE;
	}

