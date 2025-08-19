---@meta

--[[
  system.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class system
--[[
A library that allows users to get V-GAME's system status and log to the
console while debugging.
]]
system = {}

---@param ... any
--[[
Prints the data given to the function to the console. The printed message will
be formatted as an error message.
]]
function system.error(...) end

---@param code? integer
--[[
Exits the application with exit status 0 or the given exit code if provided.
]]
function system.exit(code) end

---@param ... any
--[[
Prints the data given to the function to the console. The printed message will
be formatted as an error message. This function will not exit the program when
called.
]]
function system.log(...) end

---@param message any
--[[
Throws the given error string as a fatal error and shuts down the application
if not caught by `pcall()`
]]
function system.panic(message) end

---@return number
--[[
Returns the current system tick (how many interrupts have occured).
]]
function system.tick() end

---@return number
--[[
Returns the current time in unix timestamp format.
]]
function system.time() end

---@param ... any
--[[
Prints the data given to the function to the console. The printed message will
be formatted as a warning.
]]
function system.warn(...) end

