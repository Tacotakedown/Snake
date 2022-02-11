#include <iostream>
#include "SDL.h"

#include <vector>
#include <algorithm>
#include <deque>

#undef main




int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	auto window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
	auto renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Event e;


	enum Direction
	{
		DOWN,
		LEFT,
		RIGHT,
		UP
	};

	bool running = true;

	int dir = 0;



	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect


	SDL_Rect head{ 500,500,10,10 };

	std::deque<SDL_Rect> rq;
	int size = 1;


		SDL_Rect apple;
	apple.x = rand()%100 *10;
	apple.y =rand()%100 *10;
	apple.w = 10;
	apple.h =10;

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) { running = false; }
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					if (dir == DOWN) {
						dir = DOWN;
					}
					else {
						dir = UP;
					}
				}
				if (e.key.keysym.sym == SDLK_s) {
					if (dir == UP) {
						dir = UP;
					}
					else {
						dir = DOWN;
					}
				}
				if (e.key.keysym.sym == SDLK_a) {
					if (dir == RIGHT) {
						dir == RIGHT;
					}
					else {
						dir = LEFT;
					}
					
				}
				if (e.key.keysym.sym == SDLK_d) {
					if (dir == LEFT) {
						dir == LEFT;
					}
					else {
						dir = RIGHT;
					}
				}
			}
		}


		switch (dir)
		{
		case DOWN: 
			head.y += 10; break;
		case UP:
			head.y -= 10; break;
		case LEFT:
			head.x -= 10; break;
		case RIGHT:
			head.x += 10; break;
			
		}

		
			if (head.x == apple.x && head.y == apple.y) {
				size += 10;
				apple.x = rand() % 100 * 10;
				apple.y = rand() % 100 * 10;
				};

			if (head.x >= 1001 || head.x <= -1 || head.y >= 1001 || head.y <= -1)
			{
				size = 1;
				head.x = 500;
				head.y = 500;
			}

		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment) 
			{
				if (head.x == snake_segment.x && head.y == snake_segment.y) 
				{
					size = 1;
					head.x = 500;
					head.y = 500;
				}
			});

		rq.push_front(head);
		
		while (rq.size() > size)
			rq.pop_back();
		


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);


		SDL_SetRenderDrawColor(renderer, 50, 160, 25, 255);
		std::for_each(rq.begin(), rq.end(), [&](auto& snake_segment)
			{
				SDL_RenderFillRect(renderer, &snake_segment);
			});
	

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		
			SDL_RenderFillRect(renderer, &apple);
			
	
		SDL_RenderPresent(renderer);
		SDL_Delay(50);

	}
	return 0;
}

