#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "world.hpp"

Game::Game() : _window(sf::VideoMode(640, 480), "Curse-of-time", sf::Style::Close),
	       _world(_window)
{ }
				
Game::~Game() { }

void Game::run()
{
	sf::Clock clock;
    	while (_window.isOpen())
    	{
		process_events();
		
		update();
		render();
	}
}

void Game::process_events()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
	    	if (event.type == sf::Event::Closed)
			_window.close();
	
		if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape) 
				_window.close();
		}
	}
}

void Game::update()
{

}

void Game::render()
{
	_window.clear();
	_world.draw();
	_window.display();
}

