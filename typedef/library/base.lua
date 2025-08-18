---@meta

--[[
  input.lua

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

---@param message any
---@param level? integer
--[[
Terminates the last protected function called and returns the given message. If
this function is used outside of pcall, then this function will terminate the
application. This function never returns.

Optionally, an error level can be given, which error uses to add information
towards the beginning of the error message. At level 1 (the default), the
error's position is where the `error()` function was just called. Level 2
points the error to the function containing the call to `error()`, and so on.
Passing a level of 0 avoids adding position information to the error.
]]
function error(message, level) end

---@generic T: table, V
---@param iterable T
---@return fun(iterable: V[], index?: number): integer, V
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
---@param iterable table<K, V>
---@param index? K
---@return K?
---@return V?
--[[
Returns the next key-value pair within the given iterable. This function can be
used to iterate through a table without using `pairs()` or `ipairs()` directly,
and can be used to write custom iterators. Just keep in mind that `next()` will
traverse tables in an unpredictable order!
]]
function next(iterable, index) end

---@generic T: table, K, V
---@param iterable T
---@return fun(iterable: table<K, V>, index?: K): K, V
---@return K
---@return V
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

---@param ... any
--[[
Receives any number of arguments and prints their values to stdout, converting
every value to a string if possible. This function is commonly used for
debugging reasons.
]]
function print(...) end

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

