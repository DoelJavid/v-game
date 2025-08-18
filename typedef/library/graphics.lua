---@meta

--[[
  graphics.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class graphics
--[[
Manages all graphics for V-GAME.

The vast majority of calls to the graphics library are stored internally in
graphics memory. For graphics commands to draw to the screen, you need to call
`graphics.draw()`.

Graphics memory has a limit of 255 graphics commands, and all commands are
cleared after `graphics.draw()` is called. If you were to ever reach this
limit, V-GAME will stop drawing without further notice. One must be weary of
how many times he/she's calling into the graphics library before calling
`graphics.draw()`.
]]
graphics = {}

---@return integer
--[[
Returns the current width of the game screen in pixels.
]]
function graphics.width() end

---@return integer
--[[
Returns the current height of the game screen in pixels.
]]
function graphics.height() end

---@return number
--[[
Returns a number equivalent to `graphics.height() / graphics.width()`. This
function is useful for ensuring graphics don't stretch out to the current
screen size.
]]
function graphics.aspect() end

---@return integer
--[[
Returns the current graphics index. This index will be a value between 0 and
255.
]]
function graphics.count() end

--[[
Executes all commands within graphics memory and resets the current graphics
index.

**This function will interrupt the program once called! This function must be
called or else the program will freeze!**
]]
function graphics.draw() end

--[[
  Clears the screen after a call to `graphics.draw()`.
]]
function graphics.clear() end

---@param id integer
--[[
Sets the current color to draw with from the following set of colors:
1. White
2. Red
3. Orange
4. Yellow
5. Lime
6. Light Blue
7. Blue
8. Magenta

This function is meant to be called before `graphics.draw()`.
]]
function graphics.color(id) end

--[[
Sets the current graphics position without drawing anything. This function is
meant to be called before `graphics.draw()`.
]]
function graphics.move(x, y) end

--[[
Draws a line between the current graphics position and the given position, then
moves the current graphics position to the given position. This function is
meant to be called before `graphics.draw()`.
]]
function graphics.plot(x, y) end

