#include "TextureCache.hpp"
#include <algorithm>

TextureCache* TextureCache::cache = NULL;

TextureCache::TextureCache() { }

TextureCache* TextureCache::get()
{
	if (!cache)
		cache = new TextureCache();

	return cache;
}

bool TextureCache::exists(std::string pName)
{
	std::unordered_map<std::string, Texture*>& objects = TextureCache::get()->objects;

	if (objects.find(pName) == objects.end())
		return false;
	else
		return true;
}

void TextureCache::push(Texture* obj)
{
	Texture* image = nullptr;
	std::map<std::string, Texture> * images = TextureCache::get()->objects;

	if (images->count(fileName) != 0)
		image = &(*images)[fileName];
	else
	{
		sf::Texture temp;
		temp.loadFromFile("sprites/" + fileName);
		image = &temp;
		(*images)[fileName] = temp;
	}

	return image;
}

Texture* TextureCache::find(std::string pName)
{
	auto it = TextureCache::get()->objects.find(pName);

	if (it != TextureCache::get()->objects.end())
		return it->second;
	else
		return NULL;
}

bool TextureCache::rename(std::string original, std::string replacement)
{
	std::unordered_map<std::string, Texture*>& objects = TextureCache::get()->objects;

	for (auto it = objects.begin(); it != objects.end(); )
	{
		if (it->second->getName() == original) 
		{
			Texture* obj = it->second;
			obj->setName(replacement);

			objects.erase(it); 
			objects.insert(std::pair<std::string, Texture*>(replacement, obj));

			return true;
		}
		else { ++it; }
	}
	
	return false;
}

bool TextureCache::remove(std::string name)
{
	std::unordered_map<std::string, Texture*>& objects = TextureCache::get()->objects;

	for (auto it = objects.begin(); it != objects.end(); )
	{
		if (it->second->getName() == name)
		{
			delete it->second;
			objects.erase(it);
			return true;
		}
		else { ++it; }
	}
	return false;
}