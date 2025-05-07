<<<<<<< HEAD
#pragma once 
#include "main.h"
#include <vector>

#ifndef GRAPHICS_H
#define GRAPHICS_H


extern constexpr Uint16 wWidth = 1680;
extern constexpr Uint16 wHeight = 1050;

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

typedef class UI_Element
	{
		public:
			SDL_FRect* Rect;
			SDL_Texture* Text;

			UI_Element(SDL_FRect* _rect, SDL_Texture* _Img);
	} UI;




SDL_Texture* LoadIMG(const char* path);

SDL_AppResult Init();


#endif // !GRAPHICS_H


=======
#pragma once 
#include "main.h"
#include <vector>

#ifndef GRAPHICS_H
#define GRAPHICS_H


extern constexpr Uint16 wWidth = 1680;
extern constexpr Uint16 wHeight = 1050;

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

typedef class UI_Element
	{
		public:
			SDL_FRect* Rect;
			SDL_Texture* Text;

			UI_Element(SDL_FRect* _rect, SDL_Texture* _Img);
	} UI;




SDL_Texture* LoadIMG(const char* path);

SDL_AppResult Init();


#endif // !GRAPHICS_H


>>>>>>> 8efbb6131e1c3c2e4adf6c29c57f71e25ce283d1
