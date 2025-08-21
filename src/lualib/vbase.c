/**
  src/lualib/vbase.h

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "vbase.h"

/**
  Tests if the given condition is truthy, and throws an error if it's falsy. An
  optional error message can be given to print to the console.
*/
static int luavbase_assert(lua_State* L) {
  luaL_checkany(L, 1);
  if (lua_toboolean(L, 1))
    return 0;
  return luaL_error(L, luaL_optstring(L, 2, "Assertion failed!"));
}

/**
  Tests if the type name provided in the second argument matches the type of
  the first argument. If they don't match, this function will throw a fatal
  error. This function is almost equivalent to `assert(type(value) == type)`
  except for the message.
*/
static int luavbase_check(lua_State* L) {
  luaL_checkany(L, 1);
  const char* test_type = luaL_checkstring(L, 2);
  const char* real_type_name = lua_typename(L, 1);
  const int real_type_id = lua_type(L, 1);

  // Push the typename of the value to the stack.
  lua_pushstring(L, real_type_name);

  if (real_type_id == LUA_TTABLE) {
    // Push the table's type field to the stack. If it's a string, compare it
    // with the real type name.
    lua_getfield(L, 1, "__type");

    if (lua_isstring(L, -1) && lua_equal(L, -1, -2)) {
      lua_pushvalue(L, 1);
      return 1;
    }

    // The type field isn't a string or doesn't match. Pop the `__type` field
    // from the stack.
    lua_pop(L, 1);
  }

  lua_pushstring(L, test_type);
  if (lua_equal(L, -1, -2)) {
    lua_pushvalue(L, 1);
    return 1;
  }

  return luaL_error(L, "Expected %s, but got %s!", real_type_name, test_type);
}

static int luavbase_ipairs_next(lua_State* L) {
  int idx = luaL_checkint(L, 2) + 1;

  if (lua_istable(L, 1)) {
    lua_pushinteger(L, idx);
    lua_rawgeti(L, 1, idx);
    return (lua_isnil(L, -1)) ? 0 : 2;
  } else if (lua_isstring(L, 1)) {
    size_t str_length;
    const char* str = lua_tolstring(L, 1, &str_length);

    if (idx <= str_length) {
      lua_pushinteger(L, idx);
      lua_pushlstring(L, &str[idx - 1], 1);
      return 2;
    }
    return 0;
  }
  return luaL_typerror(L, 1, "table or string");
}

static int luavbase_ipairs(lua_State* L) {
  int type = lua_type(L, 1);
  if (type == LUA_TTABLE || type == LUA_TSTRING) {
    lua_pushcfunction(L, luavbase_ipairs_next);
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 0);
    return 3;
  }
  return luaL_typerror(L, 1, "table or string");
}

static int luavbase_next(lua_State* L) {
  if (lua_istable(L, 1)) {
    lua_settop(L, 2);
    if (lua_next(L, 1))
      return 2;

    lua_pushnil(L);
    return 1;
  } else if (lua_isstring(L, 1)) {
    size_t str_length;
    const char* str = lua_tolstring(L, 1, &str_length);
    int idx = lua_tointeger(L, 2) + 1;

    if (idx <= str_length) {
      lua_pushinteger(L, idx);
      lua_pushlstring(L, &str[idx - 1], 1);
      return 2;
    }
    return 0;
  }
  return luaL_typerror(L, 1, "table or string");
}

static int luavbase_pairs(lua_State* L) {
  int type = lua_type(L, 1);
  if (type == LUA_TTABLE || type == LUA_TSTRING) {
    lua_pushcfunction(L, luavbase_next);
    lua_pushvalue(L, 1);
    lua_pushnil(L);
    return 3;
  }
  return luaL_typerror(L, 1, "table or string");
}

/**
  Calls the given function in protected mode, preventing any fatal errors
  thrown by the function from crashing the program. Pretty much the same as
  Lua 5.1's source.

  https://www.lua.org/source/5.1/lbaselib.c.html#luaB_pcall
*/
static int luavbase_pcall(lua_State* L) {
  luaL_checkany(L, 1);
  bool status = lua_pcall(L, lua_gettop(L) - 1, LUA_MULTRET, 0);
  lua_pushboolean(L, status == 0);
  lua_insert(L, 1);
  return lua_gettop(L);
}

/**
  Like check, except that it ignores the `__type` field within tables.
*/
static int luavbase_rawcheck(lua_State* L) {
  luaL_checkany(L, 1);
  const char* test_type = luaL_checkstring(L, 2);
  const char* real_type = lua_typename(L, lua_type(L, 1));

  lua_pushstring(L, real_type);
  lua_pushstring(L, test_type);
  if (lua_equal(L, -2, -1))
    return 0;

  return luaL_error(L, "Expected %s, but got %s!", test_type, real_type);
}

static int luavbase_rawtype(lua_State* L) {
  luaL_checkany(L, 1);
  lua_pushstring(L, lua_typename(L, lua_type(L, 1)));
  return 1;
}

/**
  Returns the type of the given value in the form of a string. Unlike the
  traditional `type()` function, this function supports a special case for
  tables that have a `__type` field, where it will return `table.__type` if
  it's a string.
*/
static int luavbase_type(lua_State* L) {
  luaL_checkany(L, 1);

  if (lua_type(L, 1) == LUA_TTABLE) {
    lua_pushstring(L, "__type");
    lua_rawget(L, 1);

    int custom_table_type = lua_type(L, -1);
    if (custom_table_type == LUA_TSTRING) {
      return 1;
    } else if (custom_table_type != LUA_TNIL) {
      return luaL_error(L, "Invalid table type!");
    }
  }

  lua_pushstring(L, luaL_typename(L, 1));
  return 1;
}

/**
  A helper function used by the default logic of `tostring()` to convert table
  values to strings.
*/
static int luautil_table_to_string(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);

  // luaL_buffinit will immediately effect the stack, so we should call this
  // first before doing anything else with the stack.
  luaL_Buffer table_string;
  luaL_buffinit(L, &table_string);

  // The ignore list should be of the type `table` or `nil`.
  int arg_two_type = lua_type(L, 2);
  if (arg_two_type == LUA_TNONE || arg_two_type == LUA_TNIL) {
    // Create a new table with the value.
    lua_createtable(L, 2, 0);
  } else if (arg_two_type == LUA_TTABLE) {
    // Push the currently provided ignore list to the stack.
    lua_pushvalue(L, 2);
  } else
    // Hopefully, if all things go well, this function shouldn't throw.
    return luaL_error(L, "Expected table or nil!");

  // Insert the currently passed table to the ignore list.
  lua_pushvalue(L, 1);
  lua_rawseti(L, -2, lua_objlen(L, -2) + 1);

  bool first_value = true;
  size_t current_array_index = 1;
  int tab_offset = lua_objlen(L, -1);

  // Iterate through all the keys of the table and construct a full string
  // using Lua.
  luaL_addstring(&table_string, "{\n");
  lua_pushnil(L);
  while (lua_next(L, 1)) {
    // After the call to `lua_next()`:
    // * The key should be located at stack offset -2.
    // * The value should be located at stack offset -1.

    // Account for the first value within the table.
    if (first_value)
      first_value = false;
    else
      luaL_addstring(&table_string, ",\n");

    // Add padding based on tab offset.
    for (int i = 0; i < tab_offset; i++)
      luaL_addstring(&table_string, "  ");

    // Add the key to the table string.
    //
    // In theory, the number indexes should occure in the order they're
    // declared. If they don't appear in array order, they should be
    // treated like dictionary keys.
    if (lua_isnumber(L, -2) && lua_tointeger(L, -2) == current_array_index)
      current_array_index++;
    else {
      int key_type = lua_type(L, -2);

      luaL_addstring(&table_string, "[");

      switch (key_type) {
      case LUA_TNUMBER:
        // `lua_tostring()` will convert the number in the stack to a string,
        // throwing off `lua_next()`. We need to create a duplicate.
        lua_pushvalue(L, -2);
        luaL_addstring(&table_string, lua_tostring(L, -1));
        lua_pop(L, 1);
        break;

      case LUA_TSTRING:
        luaL_addstring(&table_string, "\"");
        luaL_addstring(&table_string, lua_tostring(L, -2));
        luaL_addstring(&table_string, "\"");
        break;

      case LUA_TBOOLEAN:
        luaL_addstring(&table_string, lua_toboolean(L, -2) ? "true" : "false");
        break;

      case LUA_TTABLE:
        // Get the first value in the array of reoccuring tables. If it's equal
        // to the key, then refer to that key as "self". Otherwise, name the
        // key like any other value.
        lua_rawgeti(L, -4, 1);
        if (lua_equal(L, -3, -1))
          luaL_addstring(&table_string, "@self");
        else
          luaL_addstring(&table_string, "@table");
        lua_pop(L, 1);
        break;

      case LUA_TFUNCTION:
        luaL_addstring(&table_string, "@function");
        break;

      default:
        break;
      }

      luaL_addstring(&table_string, "] = ");
    }

    // We should avoid calling `tostring` on tables that were already indexed
    // so we won't start an infinite loop.
    switch (lua_type(L, -1)) {
    case LUA_TTABLE:
      bool duplicate_table = false;

      lua_pushnil(L);
      while (lua_next(L, -4)) {
        if (lua_rawequal(L, -1, -3)) {
          duplicate_table = true;
          lua_pop(L, 2); // Pop both key and value. We're done here.
          break;
        }

        lua_pop(L, 1);
      }

      if (duplicate_table) {
        lua_rawgeti(L, 2, 1);
        if (lua_equal(L, -2, -1))
          luaL_addstring(&table_string, "@self");
        else {
          luaL_addstring(&table_string, "@table");
        }
        lua_pop(L, 1);
      } else {
        // Call `luautil_table_to_string()` recursively to get the table value as a
        // string.

        lua_pushcfunction(L, luautil_table_to_string);
        lua_pushvalue(L, -2);
        lua_pushvalue(L, -5);
        lua_call(L, 2, 1);

        // Add that string to the result buffer.
        luaL_addstring(&table_string, lua_tostring(L, -1));
        lua_pop(L, 1);
      }
      break;
    case LUA_TSTRING:
      // In the case of a string, we need to add quotation marks around the
      // value to denote it as a string.
      lua_pushcfunction(L, luavbase_tostring);
      lua_insert(L, -2);
      lua_call(L, 1, 1);
      luaL_addstring(&table_string, "\"");
      luaL_addstring(&table_string, lua_tostring(L, -1));
      luaL_addstring(&table_string, "\"");
      break;

    default:
      // For all other values, recursively call `luavbase_tostring()`.
      lua_pushcfunction(L, luavbase_tostring);
      lua_insert(L, -2);
      lua_call(L, 1, 1);
      luaL_addstring(&table_string, lua_tostring(L, -1));
      break;
    }

    // Pop the current value out of the stack to continue iterating through the
    // Lua table.
    lua_pop(L, 1);
  }

  // Add the closing bracket to the result string and push the result to the
  // stack. Finally, return this value.
  luaL_addstring(&table_string, "\n");
  for (int i = 0; i < tab_offset - 1; i++)
      luaL_addstring(&table_string, "  ");
  luaL_addstring(&table_string, "}");

  luaL_pushresult(&table_string);
  return 1;
  // All this programming hurts your head, doesn't it? My head hurts after
  // writing this function!
}

int luavbase_tostring(lua_State* L) {
  const int type_id = lua_type(L, 1);

  switch (type_id) {
  case LUA_TNUMBER:
  case LUA_TSTRING:
    lua_pushstring(L, lua_tostring(L, 1));
    break;

  case LUA_TBOOLEAN:
    lua_pushstring(L, lua_toboolean(L, 1) ? "true" : "false");
    break;

  case LUA_TTABLE:
    lua_getfield(L, 1, "__tostring");

    if (lua_isfunction(L, -1)) {
      lua_pushvalue(L, 1);
      lua_call(L, 1, 1);
      lua_pushcfunction(L, luavbase_tostring);
      lua_insert(L, -2);
      lua_call(L, 1, 1);
    } else if (lua_isnil(L, -1)) {
      lua_pushcfunction(L, luautil_table_to_string);
      lua_pushvalue(L, 1);
      lua_call(L, 1, 1);
    } else {
      return luaL_error(L, "Expected `__tostring` to be a function or nil!");
    }

    break;
  case LUA_TFUNCTION:
    lua_pushvalue(L, 1);
    lua_call(L, 0, 1);
    lua_pushcfunction(L, luavbase_tostring);
    lua_insert(L, -2);
    lua_call(L, 1, 1);
    break;

  case LUA_TNIL:
    lua_pushstring(L, "nil");
    break;

  default:
    lua_pushstring(L, "");
    break;
  }

  return 1;
}

/**
  Attempts to convert the given Lua value to a number.

  If the given value is a table, it will first attempt to return the result of
  the table method `__tonumber`. If the `__tonumber` field doesn't exist within
  the table, this function will return 0. If the `__tonumber` field within the
  table is not a function, this function will throw an error.

  If the given value is a function, the given function will be called with no
  arguments and the return value will be returned as a number.
*/
static int luavbase_tonumber(lua_State* L) {
  const int type_id = lua_type(L, 1);

  switch (type_id) {
  case LUA_TNUMBER:
  case LUA_TSTRING:
    lua_pushnumber(L, lua_tonumber(L, 1));
    break;

  case LUA_TBOOLEAN:
    lua_pushinteger(L, lua_toboolean(L, 1));
    break;

  case LUA_TTABLE:
    lua_getfield(L, 1, "__tonumber");

    if (lua_isfunction(L, -1)) {
      lua_call(L, 0, 1);
      lua_pushcfunction(L, luavbase_tonumber);
      lua_insert(L, -2);
      lua_call(L, 1, 1);
    } else if (!lua_isnil(L, -1)) {
      return luaL_error(L, "Expected `__tonumber` to be a function or nil!");
    } else {
      lua_pushnil(L);
    }

    break;
  case LUA_TFUNCTION:
    lua_pushvalue(L, 1);
    lua_call(L, 0, 1);
    lua_pushcfunction(L, luavbase_tonumber);
    lua_insert(L, -2);
    lua_call(L, 1, 1);
    break;

  default:
    lua_pushnil(L);
    break;
  }

  return 1;
}

/**
  Sleeps for the given amount of frames.
*/
static int luavbase_sleep(lua_State* L) {
  for (int frames = luaL_checkint(L, 1); frames > 0; frames--)
    system_interrupt();
  return 0;
}

/**
  Unpacks all the contents of the given lua array, going from the given start
  index (or 1 if no start index is provided), and the given end index (or the
  end of the array if no end index is given). This value returns the result in
  the form of a tuple.
*/
static int luavbase_unpack(lua_State* L) {
  luaL_checktype(L, 1, LUA_TTABLE);
  int start_index = luaL_optint(L, 2, 1);
  int end_index = luaL_optint(L, 3, lua_objlen(L, 1));

  if (start_index > end_index)
    return 0;

  int num_unpacked = end_index - start_index + 1;
  if (num_unpacked <= 0 || !lua_checkstack(L, num_unpacked))
    return luaL_error(L, "Too many results to unpack!");

  lua_rawgeti(L, 1, start_index);
  while (start_index++ < end_index)
    lua_rawgeti(L, 1, start_index);

  return num_unpacked;
}

void luaopen_vbase(lua_State* L) {
  // clang-format off
  static const luaL_Reg luavbase_lib[] = {
    {"assert", luavbase_assert},
    {"check", luavbase_check},
    {"ipairs", luavbase_ipairs},
    {"next", luavbase_next},
    {"pairs", luavbase_pairs},
    {"pcall", luavbase_pcall},
    {"sleep", luavbase_sleep},
    {"rawcheck", luavbase_rawcheck},
    {"rawtype", luavbase_rawtype},
    {"tonumber", luavbase_tonumber},
    {"tostring", luavbase_tostring},
    {"type", luavbase_type},
    {"unpack", luavbase_unpack}
  };
  // clang-format on

  // Define V-GAME-specific base functions.
  // Use a loop for compatibility with vanilla Lua 5.1.
  for (const luaL_Reg* reg = &luavbase_lib[0];
       reg->name != NULL && reg->func != NULL; reg++) {
    lua_register(L, reg->name, reg->func);
  }
}

