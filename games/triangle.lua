--[[
  triangle.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

-------------------------------------------------------------------------------
--[[ Utilities ]]--

--[[
  Loops `x` between `m` and `n`. This function will throw an error if `m` is
  less than `n`.
]]
function loopNumber(x, m, n)
  assert(m > n, "'m' should be greater than 'n'")

  local distance = math.abs(m - n)
  local result = x

  while result > m do
    result = result - distance
  end

  while result < n do
    result = result + distance
  end

  return result
end

--[[
  Returns the given position rotated around 0, 0, or a pivot point if given.
]]
function rotatePoint(x, y, rotation, pivotX, pivotY)
  pivotX = pivotX or 0
  pivotY = pivotY or 0

  assert(type(x) == "number", "Expected `x` to be a number!")
  assert(type(y) == "number", "Expected `y` to be a number!")
  assert(type(rotation) == "number", "Expected `rotation` to be a number!")
  assert(type(pivotX) == "number", "Expected `pivotX` to be a number!")
  assert(type(pivotY) == "number", "Expected `pivotY` to be a number!")

  local movedX, movedY = x - pivotX, y - pivotY
  local xAlignment = math.cos(rotation)
  local yAlignment = math.sin(rotation)

  return movedX * xAlignment - movedY * yAlignment + pivotX,
    movedX * yAlignment + movedY * xAlignment + pivotY
end

--[[
  Returns a given position transformed to screen space.
]]
function pointToScreenSpace(x, y)
  assert(type(x) == "number", "Expected `x` to be a number!")
  assert(type(y) == "number", "Expected `y` to be a number!")
  local aspect = graphics.aspect()
  return x * aspect + ((1 - aspect) / 2), y
end

-------------------------------------------------------------------------------
----[[ Game Loop ]]----

local rotation = 0
local color = 1

while true do
  rotation = rotation + 0.025
  color = loopNumber(color + 0.025, 8.999, 1)

  local startingX, startingY = pointToScreenSpace(
    rotatePoint(0.25, 0.333, rotation, 0.5, 0.5)
  )

  graphics.clear()
  graphics.color(math.floor(color))

  graphics.move(startingX, startingY)
  graphics.plot(pointToScreenSpace(
    rotatePoint(0.5, 0.767, rotation, 0.5, 0.5)
  ))
  graphics.plot(pointToScreenSpace(
    rotatePoint(0.75, 0.333, rotation, 0.5, 0.5)
  ))
  graphics.plot(startingX, startingY)

  graphics.draw()
end
