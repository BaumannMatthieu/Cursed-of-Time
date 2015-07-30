#ifndef __WORLD__
#define __WORLD__

#include <SFML/Graphics.hpp>
#include <vector>
#include "resource_identifier.hpp"

class World : private sf::NonCopyable
{
	public:
		World(sf::RenderWindow& window);
		~World();

		void draw();
		void update(sf::Time dt);
	private:

		std::vector<std::vector<uint16_t>> 	_world;
		TextureWorld				_textures;	
		sf::RenderWindow&			_window;
};

#endif 
