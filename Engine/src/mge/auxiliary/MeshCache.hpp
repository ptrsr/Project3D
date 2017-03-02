#ifndef MESHCACHE_H
#define MESHCACHE_H

#include <unordered_map>

#include "mge/core/Mesh.hpp"

class MeshCache
{
public:
	static bool exists(std::string);
	static bool remove(std::string);
	static bool rename(std::string, std::string);
	static void push(Mesh*);
	static Mesh* find(std::string);

private:
	static MeshCache* get();
	MeshCache();

	static MeshCache* cache;

	std::unordered_map<std::string, Mesh*> objects;

	MeshCache(const World&) = delete;
	MeshCache& operator=(const World&) = delete;
};




#endif // ! OBJECTCACHE_H
