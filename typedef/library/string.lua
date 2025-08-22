---@meta string

--[[
  string.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class string
--[[
V-GAME's string library. This library contains functions for indexing and
manipulating strings. However, Lua's pattern matching functions are noticebly
missing, so all pattern matching operations need to be done manually by the
user.
]]
string = {}

---@param str string
---@param index? integer
---@return integer
--[[
Returns the character of the given string at the given index as an integer
representing an ASCII character code. If the index is out of range, this
function will return `nil`. If no index is given, the first character of the
string will be returned as an integer.
]]
function string.byte(str, index) end

---@param str string
---@param index? integer
---@return string
--[[
Returns the character of the given string at the given index as a single
character string. If the index is out of range, or if no index is given, this
function will return `nil`.
]]
function string.char(str, index) end

---@param str string
---@return integer
--[[
Returns the length of the given string going up to its null terminator.
]]
function string.length(str) end

---@param str string
---@return string
--[[
Returns a copy of the given string with all characters in lowercase.
]]
function string.lower(str) end

---@param str string
---@param start? integer
---@param finish? integer
---@return string
--[[
Returns a slice of the given string, starting at the given start index (or the
start of the string if the start index is `nil`), and ending at the given end
index (or at the null terminator if no end index is given).

If the start index is negative, then this function will start from the position
of the null terminator minus the given start index. If the position of the
start index is greater than or equal to the given end index, then this function
will return an empty string.

If the given end index is greater than the length of the string, the end index
will be truncated down to fit the length of the string.
]]
function string.slice(str, start, finish) end

---@param str string
---@return string
--[[
Returns a copy of the given string with all characters in uppercase.
]]
function string.upper(str) end

