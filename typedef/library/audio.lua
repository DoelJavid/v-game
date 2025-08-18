---@meta

--[[
  audio.lua

  Made by DoelJavid for V-GAME.

  https://github.com/DoelJavid/v-game
]]

---@class audio
--[[
V-GAME's audio manager.

The audio library contains a set of functions that allow you to generate sound
effects and even make music.

V-GAME has four audio channels to play audio within, each having their own
distinct sound. Channel 1 has a square wave, channel 2 has a triangle wave,
channel 3 has a sine wave, and channel 4 has noise. Whenever one channel is
used, nothing can play on that channel until the sound on that channel has
finished. This can cause some music and sound effects to cut off, so be
careful.
]]
audio = {}

---@class AudioInfo
---@field Semitone integer The key in which to play a sound.
---@field Volume number The key in which to play a sound.
---@field Duration number The key in which to play a sound.
--[[
A table that contains audio information to be given to a channel when playing
music or sound effects.
]]
local AudioInfo = {}

---@param channel integer
---@param info AudioInfo
--[[
Plays a sound immediately within the given channel using the given audio
information.
]]
function audio.blip(channel, info) end

