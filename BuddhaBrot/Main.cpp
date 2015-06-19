#include <iostream>
#include <SDL.h>

#include "Mandlebrot.h"

int main(int, char**) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Init();
	Calculate();

	SDL_Quit();
	return 0;
}