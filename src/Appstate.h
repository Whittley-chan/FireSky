#include <SDL3/SDL.h>

#ifndef APPSTATE_H
#define APPSTATE_H
typedef enum
	{
		MAIN_MENU = 0,
		IN_GAME = 1,
		PAUSED = 2,
		GAME_OVER = 3,
		QUIT = 4
	} GameContext;


typedef struct Appstate
	{
		SDL_Window *window;
		SDL_Renderer *renderer;

		GameContext Context;

	} Appstate;

extern Appstate* as;


#endif // !APPSTATE_H


