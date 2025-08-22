---@meta

--[[
  base.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@generic T
---@param condition T
---@param message? any
--[[
Tests if the given condition is truthy. If the test passes, this function will
return the value itself. Otherwise, this function will throw an error
containing the given error message.
]]
function assert(condition, message) end

---@param value any
---@param expect string
--[[
Tests whether or not the given value matches the given type string, and will
throw a type error if they don't match. If the given value is a table, this
function will also test if the `__type` field within the table matches the
given type string, otherwise, it will test it's raw type. This function is
useful for enforcing strict type checking.
]]
function check(value, expect) end

---@generic T: table | string, V
---@param iterable T
---@return fun(iterable: V[] | string, index?: number): integer, V
---@return T
---@return integer
--[[
Takes an iterable and returns three values: an iterator function, the table
itself, and 0. If used in a `for..in` loop, the returned iterator function will
iterate through the table starting at index 1 up to the first occurance of
`nil`.
]]
function ipairs(iterable) end

---@generic K, V
---@param iterable table<K, V> | string
---@param index? K
---@return K?
---@return (V | integer)?
--[[
Returns the next key-value pair within the given iterable. This function can be
used to iterate through a table without using `pairs()` or `ipairs()` directly,
and can be used to write custom iterators. Just keep in mind that `next()` will
traverse tables in an unpredictable order!
]]
function next(iterable, index) end

---@generic T: table | string, K, V
---@param iterable T
---@return fun(iterable: table<K, V> | string, index?: K): K, (V | integer)
---@return K
---@return (V | integer)
--[[
Takes an iterable value and returns three values: the `next()` function, the
given iterable, and nil. If used in a `for..in` loop, The returned iterator
function will iterate through all key-value pairs in a table in an
unpredictable order.
]]
function pairs(iterable) end

---@param func function
---@param ... any
---@return boolean success
---@return any ...
--[[
Calls the given function in protected mode. This means that if the given
function panics, pcall will catch the error. If the function succeeds, this
function will return true along with all values the function returned. If the
function panics, this function will return false along with an error message.

Optionally, this function can take a variable number of arguments to give to
the given function as parameters.
]]
function pcall(func, ...) end

---@param value any
---@param expect string
--[[
Tests whether or not the given value matches the given type string, and will
throw a type error if they don't match. If the given value is a table, this
function will ignore the `__type` field within it.
]]
function rawcheck(value, expect) end

---@param value any
---@return string
--[[
Returns the type of a given value unless the given value is a table. If the
given value is a table, it will return the string "table" regardless of whether
or not it contains a `__type` field.
]]
function rawtype(value) end

---@param frames? integer
--[[
Traps the program in an interrupt loop for the given amount of frames. By
default, this function will wait 1/60th of a second, since the game will always
run at 60 FPS. Be careful while calling this function, however, as this
function can stop calls to `input.tapped()` from returning true!
]]
function sleep(frames) end

---@param value any
---@return string
--[[
Returns the type of a given value unless the given value is a table.

If the value is a table, it will return the value of it's `__type` field. If
the `__type` field of a table is `nil`, then the function will return "table".
This function will error if the `__type` field of the given table isn't a
string!
]]
function type(value) end

---@param value any
---@return number
--[[
Attempts to convert the given value to a number.

If the given value is a table, it will first attempt to return the result of
the table method `__tonumber`. If the `__tonumber` method doesn't exist within
the table, this function will return 0. If the `__tonumber` field within the
table is not a function or nil, this function will throw an error.

If the given value is a function, the given function will be called with no
arguments and the return value will be returned as a number, or 0 if the
conversion fails.
]]
function tonumber(value) end

---@param value any
---@return string
--[[
Attempts to convert the given value to a string.

If the given value is a table, it will first attempt to return the result of
the table method `__tostring`. If the `__tostring` method doesn't exist within
the table, this function will walk throught the table and return a multi-line
string representing the table along with it's contents. If the `__tostring`
field within the table is not a function or nil, this function will throw an
error.

If the given value is a function, the given function will be called with no
arguments and the return value will be returned as a string.
]]
function tostring(value) end

