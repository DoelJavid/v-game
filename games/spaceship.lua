--[[
  spaceship.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

-------------------------------------------------------------------------------
--[[ Utilities ]]--

--[[
  Linear interpolates between `x` and `y` using `t` and returns the result.
]]
function lerp(x, y, t)
  assert(type(x) == "number", "Expected `x` to be a number!")
  assert(type(y) == "number", "Expected `y` to be a number!")
  assert(type(t) == "number", "Expected `t` to be a number!")
  return x + (y - x) * t
end

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
  Attempts to find the first occurance of a value within the given array `arr`
  and removes it if it's found.
]]
function removeFromArray(value, arr)
  local itemFound = false

  for idx, item in ipairs(arr) do
    if itemFound then
      arr[idx] = arr[idx + 1]
    else
      if item == value then
        itemFound = true
        arr[idx] = arr[idx + 1]
      end
    end
  end
end

-------------------------------------------------------------------------------
----[[ Point Utility Class ]]----

--[[
  Creates a new point at the given x and y positions.
]]
function Point(x, y)
  x = x or 0
  y = y or x

  assert(type(x) == "number", "Expected `x` to be a number!")
  assert(type(y) == "number", "Expected `y` to be a number!")

  local point = {
    __type = "Point",
    X = x,
    Y = y
  }

  --[[
    Rotates the point using the given rotation in radians. Optionally, this
    function can take an extra point to pivot around.
  ]]
  function point:Rotate(rotation, pivot)
    pivot = pivot or Point()

    assert(type(rotation) == "number", "Expected `rotation` to be a number!")
    assert(type(pivot) == "Point", "Expected `pivot` to be a point!")

    local movedPoint = Point(self.X - pivot.X, self.Y - pivot.Y)
    local xAlignment = math.cos(rotation)
    local yAlignment = math.sin(rotation)

    return Point(
      movedPoint.X * xAlignment - movedPoint.Y * yAlignment + pivot.X,
      movedPoint.X * yAlignment + movedPoint.Y * xAlignment + pivot.Y
    )
  end

  --[[
    Returns a new point that's equal to the current point multiplied by the
    given scale.
  ]]
  function point:Scale(factor)
    assert(type(factor) == "number", "Expected `factor` to be a number!")
    return Point(self.X * factor, self.Y * factor)
  end

  --[[
    Returns a new point that's equal to the sum of the current point and
    another given point.
  ]]
  function point:Add(other)
    assert(type(other) == "Point", "Expected `other` to be a point!")
    return Point(self.X + other.X, self.Y + other.Y)
  end

  --[[
    Linear interpolates the point between itself and another given point using
    `t` and returns a new point containing the result.
  ]]
  function point:Lerp(other, t)
    assert(type(other) == "Point", "Expected `other` to be a point!")
    assert(type(t) == "number", "Expected `t` to be a number!")
    return Point(
      self.X + (other.X - self.X) * t,
      self.Y + (other.Y - self.Y) * t
    )
  end

  --[[
    Gets the distance between the point and (0, 0).
  ]]
  function point:Distance()
    return math.sqrt(self.X * self.X + self.Y * self.Y)
  end

  --[[
    Returns a unit point of the given point. A unit point is a point in which
    the distance from the center is exactly 1.
  ]]
  function point:Unit()
    local distance = self:Distance()
    return Point(self.X / distance, self.Y / distance)
  end

  --[[
    Unwraps the point into a tuple of two numbers.
  ]]
  function point:Unwrap()
    return self.X, self.Y
  end

  --[[
    Returns an identical duplicate of the given point.
  ]]
  function point:Clone()
    return Point(self.X, self.Y)
  end

  --[[
    Returns the point translated to screen space. This function is used to
    ensure that nothing looks stretched out on screen.
  ]]
  function point:ToScreenSpace()
    local aspect = graphics.aspect()
    return Point(self.X * aspect + ((1 - aspect) / 2), self.Y)
  end

  return point
end

--[[
  Sets the graphics position to the position of the given point.
]]
function graphics.moveToPoint(point)
  assert(type(point) == "Point", "Expected `point` to be a Point!")
  graphics.move(point:Unwrap())
end

--[[
  Draws a line to the screen between the current graphics position and the
  given point.
]]
function graphics.plotPoint(point)
  assert(type(point) == "Point", "Expected `point` to be a Point!")
  graphics.plot(point:Unwrap())
end

--[[
  Converts the given rotation to a point.
]]
function pointFromRotation(rotation)
  assert(type(rotation) == "number", "Expected `rotation` to be a number!")
  return Point(math.cos(rotation), math.sin(rotation))
end

-------------------------------------------------------------------------------
----[[ Bullets & Bullet Management ]]----

local bullets = {}

--[[
  Creates a new bullet instance with the given position and velocity.
]]
function fireBullet(position, velocity)
  assert(type(position) == "Point", "Expected `position` to be a Point!")
  assert(type(velocity) == "Point", "Expected `velocity` to be a Point!")

  local bullet = {
    __type = "Bullet",
    Position = position:Clone(),
    Velocity = velocity:Clone()
  }

  --[[
    Updates the bullet.
  ]]
  function bullet:Update()
    self.Position = self.Position:Add(self.Velocity)

    if
      self.Position.X < -0.05 or self.Position.X > 1.05 or
      self.Position.Y < -0.05 or self.Position.Y > 1.05
    then
      removeFromArray(self, bullets)
    end
  end

  --[[
    Draws the bullet.
  ]]
  function bullet:Draw()
    local screenPosition = self.Position:ToScreenSpace()
    local direction = self.Velocity:Unit()

    graphics.moveToPoint(screenPosition)
    graphics.plotPoint(screenPosition:Add(direction:Scale(0.02)))
  end

  bullets[#bullets + 1] = bullet
end

--[[
  Updates and draws all bullets within the game.
]]
function updateBullets()
  for _, bullet in ipairs(bullets) do
    bullet:Update()
    bullet:Draw()
  end
end

-------------------------------------------------------------------------------
----[[ Players ]]----

--[[
  Creates a new ship instance.
]]
function Ship()
  local ship = {
    __type = "Ship",
    Position = Point(0.5),
    Velocity = Point(),
    Speed = 0.05,
    Rotation = 0,
    Bullet = nil
  }

  --[[
    Update process for the ship.
  ]]
  function ship:Update()
    if input.pressed("Left") then
    	self.Rotation = self.Rotation + 0.1
    end

    if input.pressed("Right") then
    	self.Rotation = self.Rotation - 0.1
    end

    if input.pressed("Up") then
      local targetVelocity = Point(0, self.Speed):Rotate(self.Rotation)
      self.Velocity = self.Velocity:Lerp(targetVelocity, 0.005)
      audio.blip(4, {Semitone = -250, Duration = 0.05, Volume = 0.1})
    else
      self.Velocity = self.Velocity:Lerp(Point(), 0.02)
    end

    if input.tapped("A") then
      fireBullet(self.Position, pointFromRotation(self.Rotation + math.pi / 2):Scale(0.02))
      audio.blip(1, {Semitone = 23, Duration = 0.05, Volume = 0.25})
    end

    self.Position.X =
      loopNumber(self.Position.X + self.Velocity.X, 1.05, -0.05)
    self.Position.Y =
      loopNumber(self.Position.Y + self.Velocity.Y, 1.05, -0.05)
  end

  --[[
    Draws the ship.
  ]]
  function ship:Draw()
    local tip = self.Position:
      Add(Point(0, 0.028)):
      Rotate(self.Rotation, self.Position):
      ToScreenSpace()

    graphics.color(1)
    graphics.moveToPoint(tip)

    graphics.plotPoint(
      self.Position:
        Add(Point(0.02, -0.028)):
        Rotate(self.Rotation, self.Position):
        ToScreenSpace()
    )

    graphics.plotPoint(
      self.Position:
        Add(Point(-0.02, -0.028)):
        Rotate(self.Rotation, self.Position):
        ToScreenSpace()
    )

    graphics.plotPoint(tip)
  end

  return ship
end

local ship = Ship()

-------------------------------------------------------------------------------
----[[ Game Loop ]]----

while true do
  graphics.clear()

  ship:Update()
  ship:Draw()

  updateBullets()

  graphics.draw()
end
