#include <SFML/Graphics.hpp>
#include <vector>

#include "dungeon_generation.hpp"
#include "resource_identifier.hpp"
#include "world.hpp"

World::World(sf::RenderWindow& window) : _window(window)
{
	/* Creation of the dungeon */
	Dungeon_Generator dungeon(40, std::pair<uint16_t, uint16_t>(80, 20));
	_world = dungeon.get_array();

	_textures.load(Texture::World_ID::Tileset_Dungeon, "../data/tileset_dungeon.png");
}

World::~World() { }

void World::draw()
{
	for(size_t i = 0; i < _world.size(); i++) {
		for(size_t j = 0; j < _world[i].size(); j++) {
			Dungeon_Generator::Tile tile_id = static_cast<Dungeon_Generator::Tile>(_world[i][j]);
			sf::VertexArray vertices_tile(sf::Quads, 4);

			vertices_tile[0].position = sf::Vector2f(j*TILE_SIZE, i*TILE_SIZE);
			vertices_tile[1].position = sf::Vector2f((j + 1)*TILE_SIZE, i*TILE_SIZE);
			vertices_tile[2].position = sf::Vector2f((j + 1)*TILE_SIZE, (i + 1)*TILE_SIZE);
			vertices_tile[3].position = sf::Vector2f(j*TILE_SIZE, (i + 1)*TILE_SIZE);
	
			vertices_tile[0].texCoords = sf::Vector2f(tile_id*TILE_SIZE, 0);
			vertices_tile[1].texCoords = sf::Vector2f((tile_id + 1)*TILE_SIZE, 0);
			vertices_tile[2].texCoords = sf::Vector2f((tile_id + 1)*TILE_SIZE, TILE_SIZE);
			vertices_tile[3].texCoords = sf::Vector2f(tile_id*TILE_SIZE, TILE_SIZE);

			
			sf::Texture tileset_dungeon = static_cast<sf::Texture>(_textures.get(Texture::World_ID::Tileset_Dungeon)); 
			_window.draw(vertices_tile, &tileset_dungeon);
		}
	}
}

void World::update(sf::Time dt)
{
	/* update of the scenelayer */
}

