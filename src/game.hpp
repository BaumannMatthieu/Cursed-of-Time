#ifndef __GAME__
#define __GAME__

#include "world.hpp"

class Game : private sf::NonCopyable
{
	public:
		Game();
		~Game();

		void run();
	private:
		void process_events();
		void update();
		void render();

		sf::RenderWindow		_window;
		World				_world;
};

#endif
