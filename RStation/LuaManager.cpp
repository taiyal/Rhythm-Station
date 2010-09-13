#include "LuaManager.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

template<class T> class Luna {
public:
	static void Register(lua_State *L) {
		lua_pushcfunction(L, &Luna<T>::constructor);
		lua_setglobal(L, T::className);

		luaL_newmetatable(L, T::className);
		lua_pushstring(L, "__gc");
		lua_pushcfunction(L, &Luna<T>::gc_obj);
		lua_settable(L, -3);
	}
	static int constructor(lua_State *L) {
		T* obj = new T(L);

		lua_newtable(L);
		lua_pushnumber(L, 0);
		T** a = (T**)lua_newuserdata(L, sizeof(T*));
		*a = obj;
		luaL_getmetatable(L, T::className);
		lua_setmetatable(L, -2);
		lua_settable(L, -3); // table[0] = obj;

		for (int i = 0; T::Register[i].name; i++) {
			lua_pushstring(L, T::Register[i].name);
			lua_pushnumber(L, i);
			lua_pushcclosure(L, &Luna<T>::thunk, 1);
			lua_settable(L, -3);
		}
		return 1;
	}
	static int thunk(lua_State *L) {
		int i = (int)lua_tonumber(L, lua_upvalueindex(1));
		lua_pushnumber(L, 0);
		lua_gettable(L, 1);

		T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
		lua_remove(L, -1);
		return ((*obj)->*(T::Register[i].mfunc))(L);
	}
	static int gc_obj(lua_State *L) {
		T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
		delete (*obj);
		return 0;
	}
	struct RegType {
		const char *name;
		int(T::*mfunc)(lua_State*);
	};
};

lua_State *L;

class Foo
{
public:
	Foo(lua_State *L) { }
	virtual ~Foo() { }

	int bar(lua_State *L)
	{
		std::cout << "Foo::bar()" << std::endl;
		return 0;
	}

	static const char className[];
	static const Luna<Foo>::RegType Register[];
};


const char Foo::className[] = "Foo";
const Luna<Foo>::RegType Foo::Register[] = {
	{ "bar", &Foo::bar },
	{ 0 }
};

#include "FileManager.h"

void lua_testLoad()
{
	L = lua_open();
//	luaL_openlibs(L);

	luaopen_base(L);
	luaopen_table(L);
	luaopen_string(L);
	luaopen_math(L);

	Luna<Foo>::Register(L);

	luaL_dofile(L,FileManager::GetFile("Test.lua").c_str());

//	lua_close(L);
}