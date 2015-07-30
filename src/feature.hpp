#ifndef __FEATURE__
#define __FEATURE__

#include <iostream>
#include <ctime>
#include <array>
#include <vector>

class Feature
{
	#define WIDTH_MAX_ROOM 5	
	#define WIDTH_MIN_ROOM 1
	
	public:	
		typedef struct Coord
		{
			int16_t x, y;
		} Coord;
		
		enum Type {
			Room,
			Corridor	
		};
		
	public:
		Feature();
		Feature(const Coord& pos, const std::pair<uint16_t, uint16_t> dim);
		virtual ~Feature();

		const std::pair<uint16_t, uint16_t> get_dim() const;
		const Coord get_position() const;
	
		void set_position(const Coord pos);
		void set_dim(const std::pair<uint16_t, uint16_t> dim);

		void set_coord_door(const Coord coord_door);
		const Coord get_coord_door() const;
		const Type get_type() const;

	private:
		Type _type;

		std::pair<uint16_t, uint16_t> _dim;
		Coord _pos;

		Coord _coord_door;	
};

#endif
