#define SDL_MAIN_USE_CALLBACKS

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_image.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const Uint16			wWidth = 1440;
const Uint16			wHeight = 960;

const char*             Title = "FireSky v.0.0.142";

Uint8       RenderColorR = 255;
Uint8       RenderColorG = 255;
Uint8       RenderColorB = 255;
Uint8       RenderOpaqueAlpha = 255;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Surface *ScreenSurface = nullptr;
SDL_Surface *BackgroundIMG = nullptr;
SDL_Surface *HUDIMG = nullptr;
SDL_Surface *ObjIMG = nullptr;
SDL_Texture *BackgroundTexture = nullptr;
SDL_Texture *HUDTexture = nullptr;
SDL_Texture* ObjTexture = nullptr;


SDL_FRect HUDRect = 
    {
        0,
        0,
        wWidth / 2,
        wHeight / 2,
    };

SDL_FRect ObjRect = 
	{
		720,
		480,
		64,
		64,
	};

//      Initializations:



void SDL_AppQuit(void* appstate, SDL_AppResult result) 
    {
        //SDL_DestroySurface(ScreenSurface);
        //ScreenSurface = NULL;
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
    }

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) 
    {
        if (event->type == SDL_EVENT_QUIT) 
            {
                return SDL_APP_SUCCESS;
            }
        return SDL_APP_CONTINUE;
    }

bool LoadBackgroundImage()
    {
        bool success = true;
        BackgroundIMG = IMG_Load("resources/Background_1.png");
		HUDIMG = IMG_Load("resources/2.png");
		ObjIMG = IMG_Load("resources/F_22.png");

        /*
        if (!BackgroundIMG || !HUDIMG)
            {
                success = false;
            }
        else
            {
                //ScreenSurface = SDL_GetWindowSurface(window);
                BackgroundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundIMG); 
				HUDTexture = SDL_CreateTextureFromSurface(renderer, HUDIMG);
				SDL_DestroySurface(BackgroundIMG);
                SDL_DestroySurface(HUDIMG);
            }
        */

		if (!ObjIMG)
			{
			    success = false;
			}
		else
			{
                BackgroundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundIMG);
			    ObjTexture = SDL_CreateTextureFromSurface(renderer, ObjIMG);
				SDL_DestroySurface(BackgroundIMG);
                SDL_DestroySurface(ObjIMG);
            }
        return success;
    }



void Render() 
    {
        SDL_RenderClear(renderer);
        //SDL_SetRenderDrawColor(renderer, RenderColorR, RenderColorG, RenderColorB, RenderOpaqueAlpha);
        SDL_RenderTexture(renderer, BackgroundTexture, NULL, NULL);
		//SDL_RenderTexture(renderer, HUDTexture, NULL, &HUDRect);
	    SDL_RenderTexture(renderer, ObjTexture, NULL, &ObjRect);
        SDL_RenderPresent(renderer);
    }



void Update() // 
    {
        RenderColorR = rand() % 256;
        RenderColorG = rand() % 256;
        RenderColorB = rand() % 256;
    }

SDL_AppResult SDL_AppIterate(void* appstate) // Main game loop - Everything runs in realtime
    {   
        Render();
        return SDL_APP_CONTINUE;
    }

SDL_AppResult SDL_AppInit(void **appstate, int argc, char** argv) 
    {

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))    
            {
                SDL_Log("Error initializing SDL: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }

        window = SDL_CreateWindow(Title, wWidth, wHeight, NULL);
        
        if (!window) 
            {
                SDL_Log("Error creating window: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }
        
        renderer = SDL_CreateRenderer(window, NULL);

        
        if (!renderer) 
            {
                SDL_Log("Error creating renderer: %s", SDL_GetError());
                return SDL_APP_FAILURE;
            }
        /*
        if (!LoadBackgroundImage())
            {
                SDL_Log("Image load failed.");
                return SDL_APP_FAILURE;
            }        
		*/

        if (!LoadBackgroundImage())
            {
                SDL_Log("Image load failed.");
                //return SDL_APP_FAILURE;
			}

        if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "DEBUG", "Lorem ipsum Dolor sit amet", window))
            {
                SDL_Log("Error creating debug message: %s", SDL_GetError());
            }

        return SDL_APP_CONTINUE;
    }

