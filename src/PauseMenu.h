#pragma once

#include "main.h"

#ifndef  PAUSEMENU_H
#define PAUSEMENU_H

void PauseMenuRender();
void PauseMenuMouseHandler(SDL_Event* event);
void PauseMenuChangeState(GameContext context);
#endif // ! PAUSEMENU_H






