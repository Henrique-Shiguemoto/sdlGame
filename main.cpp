#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL.h"

#include "GameConstants.h"

int main(int argc, char* argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << GameConstants::windowWidth << "\n";
	std::cout << GameConstants::windowHeight << "\n";
	std::cout << GameConstants::tileWidth << "\n";
	std::cout << GameConstants::tileHeight << std::endl;

	return 0;
}