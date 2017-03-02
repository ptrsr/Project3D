#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include <unordered_map>

#include "mge/core/World.hpp"
#include "mge/core/Texture.hpp"

class TextureCache
{
public:
	static bool exists(std::string);
	static bool remove(std::string);
	static bool rename(std::string, std::string);
	static void push(Texture*);
	static Texture* find(std::string);

private:
	static TextureCache* get();
	TextureCache();

	static TextureCache* cache;

	std::unordered_map<std::string, Texture*> objects;

	TextureCache(const World&) = delete;
	TextureCache& operator=(const World&) = delete;
};




#endif // ! OBJECTCACHE_H
