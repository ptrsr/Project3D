#include "LuaParser.hpp"
#include "mge/core/World.hpp"
#include "SFML\Window\Mouse.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Hex.hpp"
#include "ObjectCache.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

int spawn(lua_State* lua) 
{
	GameObject* obj = new GameObject(lua_tostring(lua, -1), glm::vec3(0,0,0));
	//obj->scale(glm::vec3(2, 2, 2));
	ObjectCache::push(obj);

	World::add(obj);

	return 0;
}
int exists(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
		lua_pushboolean(lua, ObjectCache::exists(lua_tostring(lua, -1)));
	else
	{
		std::cout << "error: 'exist' function isn't a string" << std::endl;
		lua_pushboolean(lua, false);
	}
	return 1;
}
int rename(lua_State* lua)
{
	if (lua_gettop(lua) == 2 && lua_isstring(lua, -1) && lua_isstring(lua, -2))
	{
		if (!ObjectCache::rename(lua_tostring(lua, -2), lua_tostring(lua, -1)))
			std::cout << "error renaming: object doesn't exist" << std::endl;
	}
	else std::cout << "error: rename param isn't a string" << std::endl;

	return 0;
}
int remove(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
	{
		if (!ObjectCache::remove(lua_tostring(lua, -1)))
			std::cout << "error deleting: object doesn't exist" << std::endl;
	}
	else std::cout << "error: delete param isn't a string" << std::endl;

	return 0;
}

int getPos(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -1));

		if (obj != nullptr)
		{
			glm::vec3 pos = obj->getWorldPosition();

			lua_pushnumber(lua, pos.x);
			lua_pushnumber(lua, pos.y);
			lua_pushnumber(lua, pos.z);
		}
		else std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: 'getPos' function param isn't a string" << std::endl;

	return 3;
}
int setPos(lua_State* lua)
{
	if (lua_gettop(lua) == 4 && lua_isnumber(lua, -1) && lua_isnumber(lua, -2) && lua_isnumber(lua, -3))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -4));

		if (obj != nullptr)
		{
			float x = 0;
			x = lua_tonumber(lua, -3);
			cout << x << endl;
			float y = 0;
			y = lua_tonumber(lua, -2);

			cout << y << endl;
			float z = 0;
			z = lua_tonumber(lua, -1);

			cout << z << endl;
			obj->setLocalPosition(glm::vec3(-x, y, z));
		}
		else
			std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: move param isn't a number" << std::endl;

	return 0;
}

int setRotation(lua_State* lua)
{
	std::cout << "Trying" << std::endl;
	if (lua_gettop(lua) == 4 && lua_isnumber(lua, -1) && lua_isnumber(lua, -2) && lua_isnumber(lua, -3))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -4));

		if (obj != nullptr)
		{

			cout << "Setting rotation" << endl;


			float x = lua_tonumber(lua, -3);
			cout << "x = " << x << endl;
			float y = lua_tonumber(lua, -2);
			cout << "y = " << y << endl;
			float z = lua_tonumber(lua, -1);
			cout << "z = " << z << endl;


			obj->rotateDegrees(-y, glm::vec3(0, 1, 0));
			obj->rotateDegrees(x, glm::vec3(1, 0, 0));
			obj->rotateDegrees(-z, glm::vec3(0, 0, 1));
		}
		else
			std::cout << "error getting rotation: object doesn't exist" << std::endl;
	}
	else std::cout << "error: rotation param isn't a number" << std::endl;

	return 0;
}



int move(lua_State* lua)
{
	if (lua_gettop(lua) == 3 && lua_isnumber(lua, -1) && lua_isnumber(lua, -2) && lua_isnumber(lua, -3))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -1));

		if (obj != nullptr)
			obj->translate(glm::vec3(lua_tonumber(lua, -3), lua_tonumber(lua, -2), lua_tonumber(lua, -1)));
		else
			std::cout << "error getting position: object doesn't exist" << std::endl;
	}
	else std::cout << "error: move param isn't a number" << std::endl;

	return 0;
}

int setTexture(lua_State* lua)
{
	int size = lua_gettop(lua);

	if (size == 0)
	{
		std::cout << "error: setTexture parameters" << std::endl;
		return 0;
	}


	GameObject* obj = ObjectCache::find(lua_tostring(lua, -size));
	
	if (!obj)
	{
		std::cout << "error: object doesn't exist" << std::endl;
		return 0;
	}

	if (size == 2 && lua_isstring(lua, -size + 1))
	{
		Texture* texture = Texture::load(config::MGE_TEXTURE_PATH + lua_tostring(lua, -size + 1));

		if (texture)
		{
			obj->setMaterial(new LitMaterial(texture, 10));
			return 0;
		}
	}
	else if (size == 4 && lua_isnumber(lua, -size + 1)) {
		obj->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3((lua_tonumber(lua, -size + 1), lua_tonumber(lua, -size + 2), lua_tonumber(lua, -size + 3)))));
	}
	else {
		obj->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(1, 1, 1)));
		std::cout << "Loading default white material" << std::endl;
	}
	return 0;
}
int setMesh(lua_State* lua)
{
	if (lua_gettop(lua) == 2 && lua_isstring(lua, -2) && lua_isstring(lua, -1))
	{
		GameObject* obj = ObjectCache::find(lua_tostring(lua, -2));

		if (!obj)
		{
			std::cout << "error setting model: object doesn't exist" << std::endl;
			return 0;
		}

		obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + lua_tostring(lua, -1)));
		//obj->scale(glm::vec3(2, 2, 2));
	}

	return 0;
}

int orbit(lua_State* lua)
{
	int size = -lua_gettop(lua);

	GameObject* obj;

	if (lua_isstring(lua, size))
	{
		obj = ObjectCache::find(lua_tostring(lua, size));

		if (!obj)
		{
			std::cout << "Error setting camera: target doesn't exist" << std::endl;
			return 0;
		}
	}

	float dist = 5.f;

	if (size == -2 && lua_isnumber(lua, size + 1))
		dist = lua_tonumber(lua, size + 1);

	World::getMainCamera()->setBehaviour(new OrbitBehaviour(obj, dist));

	return 0;
}

int luaError(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
		std::cout << + "Lua error -> " << lua_tostring(lua, -1) << std::endl;
	else
		std::cout << "error: tried printing empty string" << std::endl;

	return 0;
}
int print(lua_State* lua)
{
	if (lua_gettop(lua) == 1 && lua_isstring(lua, -1))
		std::cout << lua_tostring(lua, -1) << std::endl;
	else
		std::cout << "error: tried printing empty string" << std::endl;

	return 0;
}

LuaParser::LuaParser(std::string fileName) 
{
    lua = luaL_newstate();
    luaL_openlibs(lua);

	//binding all the functions
	{
		lua_pushcfunction(lua, spawn);
		lua_setglobal(lua, "spawn");

		lua_pushcfunction(lua, exists);
		lua_setglobal(lua, "exists");

		lua_pushcfunction(lua, getPos);
		lua_setglobal(lua, "getPos");

		lua_pushcfunction(lua, move);
		lua_setglobal(lua, "move");

		lua_pushcfunction(lua, setPos);
		lua_setglobal(lua, "setPos");

		lua_pushcfunction(lua, setRotation);
		lua_setglobal(lua, "setRotation");

		lua_pushcfunction(lua, getPos);
		lua_setglobal(lua, "getPos");

		lua_pushcfunction(lua, rename);
		lua_setglobal(lua, "rename");

		lua_pushcfunction(lua, remove);
		lua_setglobal(lua, "delete");

		lua_pushcfunction(lua, setMesh);
		lua_setglobal(lua, "setMesh");

		lua_pushcfunction(lua, setTexture);
		lua_setglobal(lua, "setTexture");

		lua_pushcfunction(lua, orbit);
		lua_setglobal(lua, "orbit");

		lua_pushcfunction(lua, print);
		lua_setglobal(lua, "print");

		lua_pushcfunction(lua, luaError);
		lua_setglobal(lua, "error");
	}

	int error = luaL_dofile(lua, (config::MGE_LUA_PATH + fileName).c_str());
	if (error) // if non-0, then an error
	{
		// the top of the stack should be the error string
		if (!lua_isstring(lua, lua_gettop(lua)))
			std::cout << "no error" << std::endl;

		// get the top of the stack as the error and pop it off
		std::cout << lua_tostring(lua, lua_gettop(lua)) << std::endl;
		lua_pop(lua, 1);
	}
	else
	{
		// if not an error, then the top of the stack will be the function to call to run the file
		lua_pcall(lua, 0, LUA_MULTRET, 0); // once again, returns non-0 on error, you should probably add a little check
	}
}

void LuaParser::update(float pStep)
{

}