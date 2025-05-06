#pragma once 
#include "main.h"

#ifndef GRAPHICS_H
#define GRAPHICS_H

extern const Uint16 wWidth;
extern const Uint16 wHeight;



SDL_Texture* LoadIMG(const char* path);
SDL_AppResult Init();

 


typedef class Background
	{
		public:
			SDL_FRect* BGRect;
			SDL_Texture* BGRImg;

			Background(SDL_FRect* _rect, SDL_Texture* _Img);

	}	BGR;

class Button  
	{  
		public:
			SDL_FRect* ButtonRect;  
			SDL_Texture* ButtonTexture;  
	
			Button(SDL_FRect* _rect, SDL_Texture* _Img); 
	};

#endif // !GRAPHICS_H


