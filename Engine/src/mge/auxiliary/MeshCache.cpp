#include "MeshCache.hpp"
#include <algorithm>

MeshCache* MeshCache::cache = NULL;

MeshCache::MeshCache() { }

MeshCache* MeshCache::get()
{
	if (!cache)
		cache = new MeshCache();

	return cache;
}

bool MeshCache::exists(std::string pName)
{
	std::unordered_map<std::string, Mesh*>& objects = MeshCache::get()->objects;

	if (objects.find(pName) == objects.end())
		return false;
	else
		return true;
}

void MeshCache::push(Mesh* obj)
{
	MeshCache::get()->objects.insert(std::pair<std::string, Mesh*>(obj->getName(), obj));
}

Mesh* MeshCache::find(std::string pName)
{
	auto it = MeshCache::get()->objects.find(pName);

	if (it != MeshCache::get()->objects.end())
		return it->second;
	else
		return NULL;
}

bool MeshCache::rename(std::string original, std::string replacement)
{
	std::unordered_map<std::string, Mesh*>& objects = MeshCache::get()->objects;

	for (auto it = objects.begin(); it != objects.end(); )
	{
		if (it->second->getName() == original) 
		{
			Mesh* obj = it->second;
			obj->setName(replacement);

			objects.erase(it); 
			objects.insert(std::pair<std::string, Mesh*>(replacement, obj));

			return true;
		}
		else { ++it; }
	}
	
	return false;
}

bool MeshCache::remove(std::string name)
{
	std::unordered_map<std::string, Mesh*>& objects = MeshCache::get()->objects;

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