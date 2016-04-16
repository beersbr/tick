#include <iostream>
#include <SDL2/sdl.h>
#include <OpenGL/opengl.h>
#include <OpenGL/gl3.h>

#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

#include "game.hpp"
#include "hogl.hpp"
#include "animations.hpp"
#include "globals.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

setup_method GameSetup;
update_method GameUpdateAndRender;
int LastLibBuildTime = 0;
void *LibHandle = 0;

int main(int argc, char* argv[]) {

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Could not init SDL 2" << std::endl;
		return 0;
	}

	SDL_Window *mainWindow = SDL_CreateWindow("Game",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              WINDOW_WIDTH,
                                              WINDOW_HEIGHT,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if(!mainWindow)
	{
		std::cout << "Could not create a window" << std::endl;
		return 0;
	}	

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GLContext mainContext = SDL_GL_CreateContext(mainWindow);
	SDL_GL_SetSwapInterval(1);
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION: " << value << std::endl;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;

	struct stat statBuffer = {};
	bool loop = true;

	GameState gameState = {};

	gameState.memory.mainMemorySz = MEGABYTES(128);
	gameState.memory.mainMemory   = mmap(0,
                                               gameState.memory.mainMemorySz,
                                               PROT_READ | PROT_WRITE,
                                               MAP_ANONYMOUS | MAP_PRIVATE,
                                               -1, 0);


	gameState.memory.transientMemorySz = GIGABYTES(2);
	gameState.memory.transientMemory   = mmap(0,
                                                    gameState.memory.transientMemorySz,
                                                    PROT_READ | PROT_WRITE,
                                                    MAP_ANONYMOUS | MAP_PRIVATE,
                                                    -1, 0);

	int currentTime = SDL_GetTicks();
	while(loop)
	{	
		int lastTime = currentTime;
		currentTime  = SDL_GetTicks();

		int elapsedTime = currentTime - lastTime;

		// NOTE(Brett): Check for the libgame.so and load the newest verion of the functions
		stat("libgame.so", &statBuffer);
		if(LastLibBuildTime == 0 || (statBuffer.st_mtime > LastLibBuildTime))
		{
			if(LibHandle)
				dlclose(LibHandle); 

			LibHandle                   = dlopen("libgame.so", RTLD_GLOBAL);
			GameUpdateAndRender         = (update_method)dlsym(LibHandle, "UpdateAndRender");
			GameSetup                   = (setup_method)dlsym(LibHandle, "Setup");
			LastLibBuildTime            = (int)statBuffer.st_mtime;
			gameState.initialized = false;
			
			GameSetup(&gameState);
		}

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				loop = false;

			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						loop = false;
						break;
					default:
						break;
				}

			}
		}
		
		GameUpdateAndRender(&gameState);
		SDL_GL_SwapWindow(mainWindow);
	}

	return 0;
}