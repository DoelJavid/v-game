---@meta

--[[
  math.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class math
---@field PI number mathematical constant representing `pi`.
---@field HUGE number A mathematical constant representing the largest possible floating-point number.
--[[
V-GAME's math library. Most of this library remains mostly the same as the Lua
math library, except for the fact that all math functions are reduced to
floating-point precision instead of double precision, and the math library is
missing.
]]
math = {}

---@param value number
---@return number
--[[
Returns the absolute value of the given number.
]]
function math.abs(value) end

---@param radians number
---@return number
--[[
Returns the arc cosine of the given angle in radians.
]]
function math.acos(radians) end

---@param radians number
---@return number
--[[
Returns the arc sine of the given angle in radians.
]]
function math.asin(radians) end

---@param radians number
---@return number
--[[
Returns the arc tangent of the given angle in radians.
]]
function math.atan(radians) end

---@param y number
---@param x number
---@return number
--[[
Returns the arc tangent of the equation `y / x`, using the signs of both
parameters to determine the result. This function also handles when `x` is
equal to zero.
]]
function math.atan2(y, x) end

---@param value number
---@return integer
--[[
Returns the value rounded up to the nearest integer.
]]
function math.ceil(value) end

---@param radians number
---@return number
--[[
Returns the cosine of the given angle in radians.
]]
function math.cos(radians) end

---@param radians number
---@return number
--[[
Returns the hyperbolic cosine of the given angle in radians.
]]
function math.cosh(radians) end

---@param power number
---@return number
--[[
Returns the mathematical constant `e` raised to the given power.
]]
function math.exp(power) end

---@param value number
---@return integer
--[[
Returns the value rounded down to the nearest integer. In other words, this
function truncates the decimal places of the given value.
]]
function math.floor(value) end

---@param value number
---@return number
--[[
Returns the values `m` and `e` that satisfy the equation `value = (m * 2) ^ e`.
`e` is an integer and the aboslute value of `m` is between the values 0.5 and 1
(or 0 if the given value is 0).
]]
function math.frexp(value) end

---@param value number
---@return integer
--[[
Returns the value type-casted to an integer value. This function is equivalent
to performing an explicit type-cast on a float to an integer in the C
programming language.
]]
function math.int(value) end

---@param m number
---@param e number
---@return number
--[[
Returns the result of the equation `(m * 2) ^ e`, where `e` is an integer
value.
]]
function math.ldexp(m, e) end

---@param value number
---@return number
--[[
Returns the natural logarithm of the given value.
]]
function math.log(value) end

---@param value number
---@return number
--[[
Returns the common logarithm of the given value.
]]
function math.log10(value) end

---@param value number
---@param ... number
---@return number
--[[
Returns the highest value out of all the given values.
]]
function math.max(value, ...) end

---@param value number
---@param ... number
---@return number
--[[
Returns the lowest value out of all the given values.
]]
function math.min(value, ...) end

---@param radians number
---@return number
--[[
Returns the sine of the given angle in radians.
]]
function math.sin(radians) end

---@param radians number
---@return number
--[[
Returns the hyperbolic sine of the given angle in radians.
]]
function math.sinh(radians) end

---@param value number
---@return number
--[[
Returns the square root of the given value.
]]
function math.sqrt(value) end

---@param radians number
---@return number
--[[
Returns the tangent of the given angle in radians.
]]
function math.tan(radians) end

---@param radians number
---@return number
--[[
Returns the hyperbolic tangent of the given angle in radians.
]]
function math.tanh(radians) end

