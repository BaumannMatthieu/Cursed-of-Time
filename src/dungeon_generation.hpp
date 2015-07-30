#ifndef __DUNGEON_GENERATION__
#define __DUNGEON_GENERATION__

#include <iostream>
#include <ctime>
#include <array>
#include <vector>

#include "resource_identifier.hpp"
#include "feature.hpp"

class Dungeon_Generator
{
	public:
		
		enum Direction {
			Up, 
			Right, 
			Down, 
			Left,
			DirectionCount
		};

		enum Tile {
			Wall,
			Wall_Against_Floor,
			Floor,
			Floor_Against_Wall,
			No,
			TileCount
		};

	public:	
	
		Dungeon_Generator(const uint16_t number_feature, std::pair<uint16_t, uint16_t> size_map);

		virtual ~Dungeon_Generator();

		void draw();
		const std::vector<std::vector<uint16_t>> get_array() const;
	private:

		void initialization();
		void add_feature();

		bool out_of_map(const Feature feature);
	
		bool intersection(const Feature first_feature, const Feature second_feature);
		bool intersection_features(const Feature feature);

		void update_array();
	
	private:
		std::vector<std::vector<uint16_t>> _dungeon;

		std::pair<uint16_t, uint16_t> _size_map;
		std::vector<Feature> _features;
};

#endif
