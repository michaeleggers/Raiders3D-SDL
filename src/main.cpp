#include <iostream>
#include <string>
#include "SDL.h"
/* Graphics */
#include "../inc/GraphicsCore.h"
/* Input */
#include "../inc/InputCore.h"

using namespace std;

size_t delay = 100;
const int FPS = 60;
const float DELAY_TIME = 1000.0f / FPS;


int main(int argc, char** argv)
{



	// Init SDL2 //////////////////////////////////////

  // for now done in graphics core

	// ! Init SDL2 //////////////////////////////////////


  // Init Graphics Core ///////////////////////////////

	bbq::GraphicsCore gCore;
	gCore.init();

	// ! Init Graphics Core /////////////////////////////

	// Init Input Core //////////////////////////////////

	bbq::InputCore iCore;
	iCore.init();

	// ! Init Input Core ////////////////////////////////



	  // ! Test SpriteSheet, Sprite classes
	bool running = true;
	size_t iter = 0;
	SDL_Event event;

	int before_update_time = 0;
	int last_update_time = SDL_GetTicks();
	float last_update_time_input = SDL_GetTicks();
	int before_render_time = SDL_GetTicks();
	int after_render_time = 0.0f;
	int time_needed = 0;

	while (running) {

		before_render_time = SDL_GetTicks();

		while (SDL_PollEvent(&event) != 0)
		{

			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		// input update
		if (SDL_GetTicks() - last_update_time_input > 10) // not quite what the threshold should be
		{
			iCore.update();

			if (iCore.keyDown(SDL_SCANCODE_DOWN))
			{

			}
			if (iCore.keyDown(SDL_SCANCODE_UP))
			{

			}
			if (iCore.keyUp(SDL_SCANCODE_RIGHT))
			{

			}
			if (iCore.keyUp(SDL_SCANCODE_LEFT))
			{

			}
			if (iCore.keyDown(SDL_SCANCODE_SPACE))
			{

			}

			if (iCore.keyDown(SDL_SCANCODE_ESCAPE))
			{

			}

			last_update_time_input = SDL_GetTicks();
		}

		// controlls animation speed
		if (SDL_GetTicks() - last_update_time > 30)
		{
			last_update_time = SDL_GetTicks();
		}

		//SDL_SetRenderDrawColor(rdr_main, 0.2, 0.2, 0.2, 255);
		gCore.clear();
		//SDL_RenderClear(rdr_main);
		//SDL_RenderCopy(rdr_main, texture, NULL, NULL);
		SDL_RenderPresent(gCore.getRenderer());
		//SDL_Delay(100); // artificial render time 

		after_render_time = SDL_GetTicks();
		time_needed = after_render_time - before_render_time;

		if (time_needed < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - time_needed);
		}

	}


	SDL_Quit();

	return 0;
}