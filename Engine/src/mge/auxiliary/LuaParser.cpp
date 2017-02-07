#include "LuaParser.hpp"
#include "mge/core/World.hpp"
#include "SFML\Window\Mouse.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Hex.hpp"

int createObject(lua_State * lua) 
{
	glm::vec3 position = glm::vec3(lua_tonumber(lua, -7), lua_tonumber(lua, -6), -lua_tonumber(lua, -5));
	glm::vec3 scale = glm::vec3(lua_tonumber(lua, -4), lua_tonumber(lua, -3), lua_tonumber(lua, -2));

	GameObject* obj = new GameObject(lua_tostring(lua, -8), position);
	obj->scale(scale);
	obj->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_unity.obj"));

	std::string hexColor = lua_tostring(lua, -1);
	glm::vec3 color = hex::HexadecimalToRGB(hexColor) / 255.0f;

	obj->setMaterial(new ColorMaterial(color));
	World::add(obj);

	return 0;
}

int getObject(lua_State* lua)
{
	std::string object = lua_tostring(lua, -1);
	std::cout << object << std::endl;

	return 0;
}

LuaParser::LuaParser(std::string fileName) 
{
    lua = luaL_newstate();
    luaL_openlibs(lua);

	lua_pushcfunction(lua, createObject);
	lua_setglobal(lua, "createObject"); 

	lua_pushcfunction(lua, getObject);
	lua_setglobal(lua, "get");

	int error = luaL_dofile(lua, (config::MGE_SCENE_PATH + fileName).c_str());
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