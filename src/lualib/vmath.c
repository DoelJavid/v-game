/**
  src/lualib/vmath.c

  Written by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
*/

#include "vmath.h"

/*
  Returns the absolute value of the given Lua number.
*/
static int luavmath_abs(lua_State* L) {
  lua_pushnumber(L, fabsf((float)luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the arc cosine of the given Lua number.
*/
static int luavmath_acos(lua_State* L) {
  lua_pushnumber(L, acosf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the arc sine of the given Lua number.
*/
static int luavmath_asin(lua_State* L) {
  lua_pushnumber(L, asinf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the arc tangent of the given Lua number.
*/
static int luavmath_atan(lua_State* L) {
  lua_pushnumber(L, atanf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the arc tangent of `y / x`, but uses the signs of both values to find
  the quadrant of the result, and handles the case of `x` being zero.
*/
static int luavmath_atan2(lua_State* L) {
  lua_pushnumber(L, atan2f(luaL_checknumber(L, 1), luaL_checknumber(L, 2)));
  return 1;
}

/*
  Returns the given Lua number rounded up to the nearest integer.
*/
static int luavmath_ceil(lua_State* L) {
  lua_pushnumber(L, ceilf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the cosine of the given Lua number.
*/
static int luavmath_cos(lua_State* L) {
  lua_pushnumber(L, cosf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the hyperbolic cosine of the given Lua number.
*/
static int luavmath_cosh(lua_State* L) {
  lua_pushnumber(L, coshf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns E to the power of the given exponent.
*/
static int luavmath_exp(lua_State* L) {
  lua_pushnumber(L, expf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the given Lua number with it's decimal place truncated.
*/
static int luavmath_floor(lua_State* L) {
  lua_pushinteger(L, floorf(luaL_checknumber(L, 1)));
  return 1;
}

/*
  Returns the values of `m` and `e` which satifies the equation `(m * 2) ^ 2`,
  The value of `e` is an integer, and the absolute value of `m` is between 1
  and 0.5.
*/
static int luavmath_frexp(lua_State* L) {
  int e;
  lua_pushnumber(L, frexpf(luaL_checknumber(L, 1), &e));
  lua_pushinteger(L, e);
  return 1;
}

/*
  Returns the given lua number casted directly to an integer. This function is
  equvalent to using `(int)number` in C.
*/
static int luavmath_int(lua_State* L) {
  lua_pushinteger(L, (int)luaL_checknumber(L, 1));
  return 1;
}

/*
  Returns the result of the equation `(m * 2) ^ e` when `e` is an integer.
*/
static int luavmath_ldexp(lua_State* L) {
  lua_pushnumber(L, ldexpf(luaL_checknumber(L, 1), luaL_checkint(L, 2)));
  return 1;
}

/*
  Returns the natural logarithm of the given Lua number.
*/
static int luavmath_log(lua_State* L) {
  lua_pushnumber(L, logf(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the common logarithm of the given Lua number.
*/
static int luavmath_log10(lua_State* L) {
  lua_pushnumber(L, log10f(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the maximum number of all given Lua numbers.
*/
static int luavmath_max(lua_State* L) {
  size_t n_args = lua_gettop(L);
  lua_Number max_value = luaL_checknumber(L, 1);
  for (int i = 2; i <= n_args; i++) {
    lua_Number next_value = luaL_checknumber(L, i);
    if (next_value > max_value)
      max_value = next_value;
  }
  lua_pushnumber(L, max_value);
  return 1;
}

/**
  Returns the minimum number of all given Lua numbers.
*/
static int luavmath_min(lua_State* L) {
  size_t n_args = lua_gettop(L);
  lua_Number min_value = luaL_checknumber(L, 1);
  for (int i = 2; i <= n_args; i++) {
    lua_Number next_value = luaL_checknumber(L, i);
    if (next_value < min_value)
      min_value = next_value;
  }
  lua_pushnumber(L, min_value);
  return 1;
}

/**
  Returns the sine of the given Lua number.
*/
static int luavmath_sin(lua_State* L) {
  lua_pushnumber(L, sinf(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the hyperbolic sine of the given Lua number.
*/
static int luavmath_sinh(lua_State* L) {
  lua_pushnumber(L, sinhf(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the square root of the given Lua number.
*/
static int luavmath_sqrt(lua_State* L) {
  lua_pushnumber(L, sqrtf(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the tangent of the given Lua number.
*/
static int luavmath_tan(lua_State* L) {
  lua_pushnumber(L, tanf(luaL_checknumber(L, 1)));
  return 1;
}

/**
  Returns the hyperbolic tangent of the given Lua number.
*/
static int luavmath_tanh(lua_State* L) {
  lua_pushnumber(L, tanhf(luaL_checknumber(L, 1)));
  return 1;
}

void luaopen_vmath(lua_State* L) {
  // Probably the largest library in the entire runtime.
  static const luaL_Reg luavmath_lib[] = {
    {"abs", luavmath_abs},
    {"acos", luavmath_acos},
    {"asin", luavmath_asin},
    {"atan", luavmath_atan},
    {"atan2", luavmath_atan2},
    {"ceil", luavmath_ceil},
    {"cos", luavmath_cos},
    {"cosh", luavmath_cosh},
    {"exp", luavmath_exp},
    {"floor", luavmath_floor},
    {"frexp", luavmath_frexp},
    {"int", luavmath_int},
    {"ldexp", luavmath_ldexp},
    {"log", luavmath_log},
    {"log10", luavmath_log10},
    {"max", luavmath_max},
    {"min", luavmath_min},
    {"sin", luavmath_sin},
    {"sinh", luavmath_sinh},
    {"sqrt", luavmath_sqrt},
    {"tan", luavmath_tan},
    {"tanh", luavmath_tanh},
    {NULL, NULL}
  };

  luaL_register(L, "math", luavmath_lib);
  lua_pushnumber(L, LUALIB_MATH_PI);
  lua_setfield(L, -2, "PI");

  lua_pushnumber(L, HUGE_VALF);
  lua_setfield(L, -2, "HUGE");
}

