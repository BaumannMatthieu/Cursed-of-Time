#include <iostream>
#include <algorithm>
#include <ctime>
#include <array>
#include <vector>

#include "feature.hpp"
#include "dungeon_generation.hpp"
#include "resource_identifier.hpp"

Dungeon_Generator::Dungeon_Generator(const uint16_t number_feature, std::pair<uint16_t, uint16_t> size_map) : _size_map(size_map)
{
	std::srand(std::time(0));
	
	initialization();

	for(uint16_t i = 0; i < number_feature; i++)
		add_feature();
		
}

Dungeon_Generator::~Dungeon_Generator() { }		

/* Initialization of the dungeon map with NO_TILE */
void Dungeon_Generator::initialization()
{
	_dungeon.resize(_size_map.second, std::vector<uint16_t>(_size_map.first, Tile::No));
}

void Dungeon_Generator::add_feature()
{
	uint16_t w = (std::rand() % WIDTH_MAX_ROOM) + WIDTH_MIN_ROOM + 2;
	uint16_t h = (std::rand() % WIDTH_MAX_ROOM) + WIDTH_MIN_ROOM + 2;
	
	Feature::Coord pos;			

	if(_features.empty()) {
		pos.x = (_size_map.first - w)/2;
		pos.y = (_size_map.second - h)/2;

		Feature new_feature(pos, std::pair<uint16_t, uint16_t>(w, h));							
		_features.push_back(new_feature);

	} else {

		Feature current_feature, new_feature;
		uint16_t id_feature;
		uint16_t dir_feature;
		
		uint16_t id_door_current_feature_x;
		uint16_t id_door_new_feature_x;
		uint16_t id_door_current_feature_y;
		uint16_t id_door_new_feature_y;

		do {
			id_feature = std::rand() % _features.size();
			dir_feature = std::rand() % DirectionCount;
			
			current_feature = _features.at(id_feature);
			
			id_door_current_feature_x = (std::rand() % (current_feature.get_dim().first - 2)) + 1;
			id_door_new_feature_x = (std::rand() % (w - 2)) + 1;
			id_door_current_feature_y = (std::rand() % (current_feature.get_dim().second - 2)) + 1;
			id_door_new_feature_y = (std::rand() % (h - 2)) + 1;

			switch(dir_feature) {
				case Up:
					pos.x = current_feature.get_position().x - (id_door_new_feature_x - id_door_current_feature_x);
					pos.y = current_feature.get_position().y - h + 1;
				break;						
				case Down:
					pos.x = current_feature.get_position().x - (id_door_new_feature_x - id_door_current_feature_x);
					pos.y = current_feature.get_position().y + current_feature.get_dim().second - 1;
				break;						
				case Right:
					pos.x = current_feature.get_position().x + current_feature.get_dim().first - 1;
					pos.y = current_feature.get_position().y - (id_door_new_feature_y - id_door_current_feature_y);
				break;						
				case Left:
					pos.x = current_feature.get_position().x - w + 1;
					pos.y = current_feature.get_position().y - (id_door_new_feature_y - id_door_current_feature_y);
				break;						
				default:
				break;
			}
			new_feature.set_position(pos);
			new_feature.set_dim(std::pair<uint16_t, uint16_t>(w, h));
			
		} while(intersection_features(new_feature) || out_of_map(new_feature));					
		/* Draw the door */
		Feature::Coord pos_door;
		if(dir_feature == Up || dir_feature == Down) {
			pos_door.x = current_feature.get_position().x + id_door_current_feature_x;
			if(dir_feature == Down) 
				pos_door.y = pos.y;
			else 
				pos_door.y = pos.y + h - 1;
		} else if(dir_feature == Left || dir_feature == Right) {
			if(dir_feature == Right) 
				pos_door.x = pos.x;
			else 
				pos_door.x = pos.x + w - 1;

			pos_door.y = current_feature.get_position().y + id_door_current_feature_y;
		}
		new_feature.set_coord_door(pos_door);

		_features.push_back(new_feature);
	}

	update_array();
}

const std::vector<std::vector<uint16_t>> Dungeon_Generator::get_array() const
{
	return _dungeon;
}

void Dungeon_Generator::draw()
{
	for(auto it_height = _dungeon.begin(); it_height != _dungeon.end(); it_height++) {
		for(auto it_width = (*it_height).begin(); it_width != (*it_height).end(); it_width++) {
			std::cout << *it_width;
		}
		std::cout << std::endl;
	}
}	

bool Dungeon_Generator::out_of_map(const Feature feature)
{
	const Feature::Coord pos = feature.get_position();
	const std::pair<uint16_t, uint16_t> dimension = feature.get_dim();
	const uint16_t w = dimension.first;
	const uint16_t h = dimension.second;

	return (pos.x < 0) || (pos.y < 0) || (pos.x + w - 1 >= _size_map.first) || (pos.y + h - 1 >= _size_map.second);
}

bool Dungeon_Generator::intersection(const Feature first_feature, const Feature second_feature) 
{
	const Feature::Coord pos_first = first_feature.get_position();
	const uint16_t w_first = first_feature.get_dim().first;
	const uint16_t h_first = first_feature.get_dim().second;
	const Feature::Coord pos_second = second_feature.get_position();
	const uint16_t w_second = second_feature.get_dim().first;
	const uint16_t h_second = second_feature.get_dim().second;

	if((std::max(std::abs(pos_first.x + w_first - pos_second.x), std::abs(pos_second.x + w_second - pos_first.x)) < w_first + w_second - 1) &&
	   (std::max(std::abs(pos_first.y + h_first - pos_second.y), std::abs(pos_second.y + h_second - pos_first.y)) < h_first + h_second - 1)) {
		return true;
	}

	return false;
}

bool Dungeon_Generator::intersection_features(const Feature feature)
{
	for(auto it_features = _features.begin(); it_features != _features.end(); it_features++) {
		if(intersection(feature, *it_features)) {
			return true;
		}
	}

	return false;
}

void Dungeon_Generator::update_array()
{
	Feature current_feature = _features.back();
	Feature::Coord pos = current_feature.get_position();
	uint16_t width = current_feature.get_dim().first;
	uint16_t height = current_feature.get_dim().second;

	/* Add the feature to the dungeon */
	for(uint16_t i = pos.y; i < pos.y + height; i++) {
		for(uint16_t j = pos.x;j < pos.x + width; j++) {
			_dungeon[i][j] = Tile::Floor;
		}
	}

	/* And the wall */
	for(uint16_t i = pos.y; i < pos.y + height; i++) {
			_dungeon[i][pos.x] = Tile::Wall;
			_dungeon[i][pos.x + width - 1] = Tile::Wall;
	}	

	for(uint16_t j = pos.x;j < pos.x + width; j++) {
			_dungeon[pos.y + height - 1][j] = Tile::Wall;
			_dungeon[pos.y][j] = Tile::Wall;
	}

	/* Draw the door of the feature */
	if(_features.size() > 1) {
		const Feature::Coord pos_door = current_feature.get_coord_door();
		
		if(current_feature.get_type() != Feature::Corridor) {
			if(_dungeon[pos_door.y - 1][pos_door.x] == Tile::Floor_Against_Wall) 
				_dungeon[pos_door.y - 1][pos_door.x] = Tile::Floor;
		} else { 
			_dungeon[pos_door.y][pos_door.x] = Tile::Floor;
			if(_dungeon[pos_door.y - 1][pos_door.x] == Tile::Floor_Against_Wall)
				_dungeon[pos_door.y - 1][pos_door.x] = Tile::Floor;	
		}
	}

	/* Draw the floor up to a wall */
	for(uint16_t j = pos.x; j < pos.x + width; j++) {
		if(_dungeon[pos.y + height - 2][j] == Tile::Floor &&
		  (_dungeon[pos.y + height - 1][j] == Tile::Wall||_dungeon[pos.y + height - 1][j] == Tile::Wall_Against_Floor)) {
			_dungeon[pos.y + height - 2][j] = Tile::Floor_Against_Wall;
		}
	}

	/* Draw the wall up to a floor tile */
	for(uint16_t i = pos.y; i < pos.y + height; i++) {
		if(i < _dungeon.size() - 1) {
			for(uint16_t j = pos.x;j < pos.x + width; j++) {
				if(_dungeon[i][j] == Tile::Wall &&
				  (_dungeon[i + 1][j] == Tile::Floor||_dungeon[i + 1][j] == Tile::Floor_Against_Wall)) {
					_dungeon[i][j] = Tile::Wall_Against_Floor;
				}
			}
		}
	}
}



