#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

#include "feature.hpp"

Feature::Feature() { }

Feature::Feature(const Coord& pos, const std::pair<uint16_t, uint16_t> dim) : _pos(pos), _dim(dim)
{
	_type = Room;

	if(dim.first == 3 || dim.second == 3) {
		_type = Corridor;
	}
}

Feature::~Feature() { }

const std::pair<uint16_t, uint16_t> Feature::get_dim() const
{
	return _dim;
}

const Feature::Coord Feature::get_position() const
{
	return _pos;
}

void Feature::set_position(const Coord pos)
{
	_pos = pos;	
}

void Feature::set_dim(const std::pair<uint16_t, uint16_t> dim)
{
	_dim = dim;
	_type = Room;

	if(dim.first == 3||dim.second == 3) {
		_type = Corridor;
	}
}

void Feature::set_coord_door(const Feature::Coord coord_door)
{
	_coord_door = coord_door;
}

const Feature::Coord Feature::get_coord_door() const
{
	return _coord_door;
}

const Feature::Type Feature::get_type() const
{
	return _type;
}


