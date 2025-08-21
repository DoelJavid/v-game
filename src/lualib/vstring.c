/**
  src/lualib/vstring.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "vstring.h"

/**
  Returns the character of the given Lua string at the given index as an
  integer representing an ASCII character code. If the index is out of range,
  this function will return `nil`. If no index is given, the first character of
  the string will be returned as an integer.
*/
static int luavstring_byte(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  size_t byte_location = luaL_optint(L, 2, 1);

  if (byte_location > str_length) {
    lua_pushnil(L);
    return 1;
  }

  lua_pushinteger(L, str[byte_location - 1]);
  return 1;
}

/**
  Returns the character of the given Lua string at the given index as a Lua
  string value. If the index is out of range, or if no index is given, this
  function will return `nil`.
*/
static int luavstring_char(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  size_t byte_location = luaL_checkint(L, 2);

  if (byte_location > str_length) {
    lua_pushnil(L);
    return 1;
  }

  lua_pushlstring(L, &str[byte_location - 1], 1);
  return 1;
}

/**
  Returns the length of the given string going up to its null terminator.
*/
static int luavstring_length(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  lua_pushinteger(L, str_length);
  return 1;
}

/**
  Returns a copy of the string with all characters in lowercase.
*/
static int luavstring_lower(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  char new_str[str_length];

  for (int i = 0; i < str_length; i++)
    new_str[i] = tolower(str[i]);

  lua_pushlstring(L, new_str, str_length);
  return 1;
}

/**
  Returns a slice of the given string, starting at the given start index (or
  the start of the string if the start index is `nil`), and ending at the given
  end index (or at the null terminator if no end index is given). If the start
  index is negative, then this function will start from the position of the
  null terminator minus the given start index. If the position of the start
  index is greater than the given end index, then this function will return
  `nil`.
*/
static int luavstring_slice(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  size_t start = luaL_optint(L, 2, 1);
  size_t end = luaL_optint(L, 3, str_length);

  if (start < 0)
    start += str_length;

  size_t slice_length = end - start;
  if (slice_length < 0) {
    lua_pushstring(L, "");
    return 1;
  }

  lua_pushlstring(L, &str[start - 1], slice_length);
  return 1;
}

/**
  Returns a copy of the string with all characters in uppercase.
*/
static int luavstring_upper(lua_State* L) {
  size_t str_length;
  const char* str = luaL_checklstring(L, 1, &str_length);
  char new_str[str_length];

  for (int i = 0; i < str_length; i++)
    new_str[i] = toupper(str[i]);

  lua_pushlstring(L, new_str, str_length);
  return 1;
}

void luaopen_vstring(lua_State* L) {
  // clang-format off
  static const luaL_Reg luastring_lib[] = {
    {"byte", luavstring_byte},
    {"char", luavstring_char},
    {"length", luavstring_length},
    {"lower", luavstring_lower},
    {"slice", luavstring_slice},
    {"upper", luavstring_upper},
    {NULL, NULL}
  };
  // clang-format on

  luaL_register(L, "string", luastring_lib);
}

