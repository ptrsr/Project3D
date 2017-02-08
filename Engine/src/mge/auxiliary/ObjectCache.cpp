#include "ObjectCache.hpp"
#include <algorithm>

ObjectCache* ObjectCache::cache = NULL;

ObjectCache::ObjectCache() { }

ObjectCache* ObjectCache::get()
{
	if (!cache)
		cache = new ObjectCache();

	return cache;
}

bool ObjectCache::exists(std::string pName)
{
	std::unordered_map<std::string, GameObject*>& objects = ObjectCache::get()->objects;

	if (objects.find(pName) == objects.end())
		return false;
	else
		return true;
}

void ObjectCache::push(GameObject* obj)
{
	ObjectCache::get()->objects.insert(std::pair<std::string, GameObject*>(obj->getName(), obj));
}

GameObject* ObjectCache::find(std::string pName)
{
	auto it = ObjectCache::get()->objects.find(pName);

	if (it != ObjectCache::get()->objects.end())
		return it->second;
	else
		return NULL;
}

bool ObjectCache::rename(std::string original, std::string replacement)
{
	std::unordered_map<std::string, GameObject*>& objects = ObjectCache::get()->objects;

	for (auto it = objects.begin(); it != objects.end(); )
	{
		if (it->second->getName() == original) 
		{
			GameObject* obj = it->second;
			obj->setName(replacement);

			objects.erase(it); 
			objects.insert(std::pair<std::string, GameObject*>(replacement, obj));

			return true;
		}
		else { ++it; }
	}
	
	return false;
}

bool ObjectCache::remove(std::string name)
{
	std::unordered_map<std::string, GameObject*>& objects = ObjectCache::get()->objects;

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