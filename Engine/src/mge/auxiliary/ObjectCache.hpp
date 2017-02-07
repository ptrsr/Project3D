#ifndef OBJECTCACHE_H
#define OBJECTCACHE_H

#include <unordered_map>

#include "mge/core/GameObject.hpp"

class ObjectCache
{
public:
	static bool exists(std::string);
	static bool remove(std::string);
	static bool rename(std::string, std::string);
	static void push(GameObject*);
	static GameObject* find(std::string);

private:
	static ObjectCache* get();
	ObjectCache();

	static ObjectCache* cache;

	std::unordered_map<std::string, GameObject*> objects;

	ObjectCache(const World&) = delete;
	ObjectCache& operator=(const World&) = delete;
};




#endif // ! OBJECTCACHE_H
