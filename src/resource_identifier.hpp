#ifndef __RESOURCE_IDENTIFIER__
#define __RESOURCE_IDENTIFIER__

#include <SFML/Graphics.hpp>
#include "resource_holder.hpp"

namespace Texture
{
	#define TILE_SIZE 64

	enum World_ID {
		Tileset_Dungeon,
		Tileset_Player,
		Tileset_Skeleton
	};
};

typedef Resource_Holder<Texture::World_ID, sf::Texture> TextureWorld;

#endif
