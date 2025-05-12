#pragma once


#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "main.h"

extern SDL_FRect* ScoreboardRect;
extern SDL_FRect* WaveBoardRect;
extern SDL_FRect* HPRect;


extern SDL_FRect* MainMenuBackgroundRect;
extern SDL_FRect* PlayButtonRect;
extern SDL_FRect* QuitButtonRect;
extern SDL_FRect* PauseQuitButtonRect;


extern SDL_FRect* PauseButtonRect;
extern SDL_FRect* PauseMenuRect;
extern SDL_FRect* ResumeButtonRect;

extern SDL_FRect* RestartButtonRect;
extern SDL_FRect* GameOverQuitButtonRect;
extern SDL_FRect* GameOverTitleRect;
extern SDL_FRect* FinalScoreRect;
extern SDL_FRect* GameOverBackgroundRect;

extern SDL_FRect* UpgradeMenuTitleRect;
extern SDL_FRect* UpgradeButtonGatlingRect;
extern SDL_FRect* UpgradeButtonRocketRect;

extern SDL_FRect* LeaderboardRect;
extern SDL_FRect* HighscoreRect;


SDL_Texture* LoadFont(const char* contents, float size);

#endif // !ELEMENTS_H
