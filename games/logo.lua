--[[
  logo.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

-------------------------------------------------------------------------------

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

-------------------------------------------------------------------------------

local color = 1

graphics.clear()
graphics.color(color)
graphics.draw()

while true do
  graphics.clear()

  -- 'V'
  graphics.color(color)
  graphics.move(0.05, 0.6)
  graphics.plot(0.125, 0.45)
  graphics.plot(0.2, 0.6)
  graphics.plot(0.05, 0.6)
  color = loopNumber(color + 1, 9, 1)

  -- '-'
  graphics.color(color)
  graphics.move(0.2, 0.5)
  graphics.plot(0.2825, 0.5)
  graphics.plot(0.2825, 0.535)
  graphics.plot(0.2, 0.535)
  graphics.plot(0.2, 0.5)
  color = loopNumber(color + 1, 9, 1)

  -- 'G'
  graphics.color(color)
  graphics.move(0.45, 0.6)
  graphics.plot(0.3125, 0.6)
  graphics.plot(0.3125, 0.45)
  graphics.plot(0.45, 0.45)
  graphics.plot(0.45, 0.525)
  graphics.plot(0.4, 0.525)
  color = loopNumber(color + 1, 9, 1)

  -- 'A'
  graphics.color(color)
  graphics.move(0.475, 0.45)
  graphics.plot(0.625, 0.45)
  graphics.plot(0.55, 0.6)
  graphics.plot(0.475, 0.45)
  color = loopNumber(color + 1, 9, 1)

  -- 'M'
  graphics.color(color)
  graphics.move(0.65, 0.45)
  graphics.plot(0.8, 0.45)
  graphics.plot(0.8, 0.6)
  graphics.plot(0.725, 0.45)
  graphics.plot(0.65, 0.6)
  graphics.plot(0.65, 0.45)
  color = loopNumber(color + 1, 9, 1)

  -- 'E'
  graphics.color(color)
  graphics.move(0.95, 0.45)
  graphics.plot(0.825, 0.45)
  graphics.plot(0.825, 0.525)
  graphics.plot(0.95, 0.525)
  graphics.move(0.825, 0.525)
  graphics.plot(0.825, 0.6)
  graphics.plot(0.95, 0.6)
  color = loopNumber(color - 4, 9, 1)

  graphics.draw()
  sleep(4)
end
