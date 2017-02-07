#ifndef LUAPARSER_H
#define LUAPARSER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/lua/lua.hpp"

class LuaParser : public AbstractBehaviour {
    
public:
    LuaParser(std::string fileName = "main.lua");
	static std::string func;
    
	virtual void update(float pStep);
	void message(send::Message) { };

private:
    lua_State * lua;


};

#endif
