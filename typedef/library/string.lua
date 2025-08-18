---@meta string

--[[
  input.lua

  Copied from Lua Language Server.

  https://github.com/LuaLS/lua-language-server/blob/master/meta/template/string.lua
]]

---#DES 'string'
---@class stringlib
string = {}

---#DES 'string.byte'
---@param s  string|number
---@param i? integer
---@param j? integer
---@return integer ...
---@nodiscard
function string.byte(s, i, j) end

---#DES 'string.char'
---@param byte integer
---@param ... integer
---@return string
---@nodiscard
function string.char(byte, ...) end

---#DES 'string.find'
---@param s       string|number
---@param pattern string|number
---@param init?   integer
---@param plain?  boolean
---@return integer|nil start
---@return integer|nil end
---@return any|nil ... captured
---@nodiscard
function string.find(s, pattern, init, plain) end

---#DES 'string.format'
---@param s string|number
---@param ... any
---@return string
---@nodiscard
function string.format(s, ...) end

---#DES 'string.gmatch'
---#if VERSION <= 5.3 then
---@param s       string|number
---@param pattern string|number
---@return fun():string, ...
---@nodiscard
function string.gmatch(s, pattern) end
---#else
---@param s       string|number
---@param pattern string|number
---@param init?   integer
---@return fun():string, ...
function string.gmatch(s, pattern, init) end
---#end

---#DES 'string.gsub'
---@param s       string|number
---@param pattern string|number
---@param repl    string|number|table|function
---@param n?      integer
---@return string
---@return integer count
function string.gsub(s, pattern, repl, n) end

---#DES 'string.len'
---@param s string|number
---@return integer
---@nodiscard
function string.len(s) end

---#DES 'string.lower'
---@param s string|number
---@return string
---@nodiscard
function string.lower(s) end

---#DES 'string.match'
---@param s       string|number
---@param pattern string|number
---@param init?   integer
---@return any ...
---@nodiscard
function string.match(s, pattern, init) end

---@param s    string|number
---@param n    integer
---@param sep? string|number
---@return string
---@nodiscard
function string.rep(s, n, sep) end

---#DES 'string.reverse'
---@param s string|number
---@return string
---@nodiscard
function string.reverse(s) end

---#DES 'string.sub'
---@param s  string|number
---@param i  integer
---@param j? integer
---@return string
---@nodiscard
function string.sub(s, i, j) end

---@version >5.3
---#DES 'string.unpack'
---@param fmt  string
---@param s    string
---@param pos? integer
---@return any ...
---@nodiscard
function string.unpack(fmt, s, pos) end

---#DES 'string.upper'
---@param s string|number
---@return string
---@nodiscard
function string.upper(s) end

