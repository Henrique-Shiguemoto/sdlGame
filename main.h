#pragma once

///////////////// Inclusions /////////////////////////////
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_thread.h"
#include "GameConstants.h"

//////////////// Type Definitions ////////////////////////

typedef struct Rect{
	float x;
	float y;
	float w;
	float h;
} Rect;

typedef struct Player{
	Rect rect;
	SDL_Surface* imageSurface;
	float speed;
} Player;

typedef struct Enemy{
	Rect rect;
	SDL_Surface* imageSurface;
	float speedX;
	float speedY;
} Enemy;

/////////////// Macro Definitions ////////////////////////

#define MAX_ENEMIES 			8
#define TARGET_FPS 				60

/////////////// Namespaces Used //////////////////////////

using namespace GameConstants;

/////////////// Function Declarations ////////////////////

void InitializeEntity(Player* p);
void printEntityPosition(Player* p);
void InitializeEntity(Enemy* p);
void printEntityPosition(Enemy* e);
unsigned int RandomInRange(unsigned int min, unsigned int max);
bool IsColliding(Rect object1, Rect object2);
char RandomSign(void);
void ProcessInput();
void SimulateWorld();
void RenderGraphics();