#include <iostream>
#include <SDL.h>

#include "Mandlebrot.h"

int main(int, char**) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Init();

	int r = 0, g = 1, b = 2;

	SDL_Thread * red = SDL_CreateThread(Calculate, "Red Thread", (void *)&r);
	SDL_Thread * green = SDL_CreateThread(Calculate, "Green Thread", (void *)&g);
	SDL_Thread * blue = SDL_CreateThread(Calculate, "Blue Thread", (void *)&b);

	SDL_WaitThread(red, &r);
	SDL_WaitThread(green, &g);
	SDL_WaitThread(blue, &b);

	DumpImage();


	SDL_Quit();
	return 0;
}