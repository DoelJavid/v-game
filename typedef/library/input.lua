---@meta

--[[
  input.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class input
input = {}

---@alias ButtonName
---
---The 'Start' button towards the center of the controller.
---| "Start"
---
---The 'Select' button towards the center of the controller.
---
---| "Select"
---
---The up direction of the controller's D-Pad.
---
---| "Up"
---
---The right direction of the controller's D-Pad.
---
---| "Right"
---
---The down direction of the controller's D-Pad.
---
---| "Down"
---
---The left direction of the controller's D-Pad.
---
---| "Left"
---
---The 'A' button towards the right of the controller.
---
---| "A"
---
---The 'B' button towards the right of the controller.
---
---| "B"
---
---The 'C' button towards the right of the controller.
---
---| "C"
---
---The 'D' button towards the right of the controller.
---
---| "D"
---
---The 'L' bumper on the top of the controller.
---
---| "L"
---
---The 'R' bumper on the top of the controller.
---
---| "R"

---@alias ControllerStatus {[ButtonName]: boolean}   A table containing the status of all controller buttons.

---@param button ButtonName | integer
---@return boolean
--[[
Returns true if the given button is being held down and false if otherwise.
]]
function input.pressed(button) end

---@param button ButtonName | integer
---@return boolean
--[[
Returns true if the given button has recently been tapped and false if
otherwise. To detect if the button is being held down, use `input.pressed`.
]]
function input.tapped(button) end

---@return ControllerStatus
--[[
Returns a table containing the current status of all buttons.
]]
function input.grab() end

