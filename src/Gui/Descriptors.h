#pragma once

#include <string>
#include <functional>
#include "lua.h"

namespace Luwow::Gui {

struct WindowDescriptor {
    std::string Type = "";
    std::string Title = "";
    int Width = 0;
    int Height = 0;
    int Left = 0;
    int Top = 0;
};

struct ButtonDescriptor {
    std::string Type = "";
    std::string Caption = "";
    lua_State* L = nullptr;           // Lua state for callback
    int OnPressedRef = LUA_NOREF;     // Lua registry reference to callback function
    int Width = 0;
    int Height = 0;
    int Left = 0;
    int Top = 0;
};

struct TextBoxDescriptor {
    std::string Type = "";
    std::string Text = "";
    std::string Font = "";
    bool MultiLineMode = false;
    int Width = 0;
    int Height = 0;
    int Left = 0;
    int Top = 0;
};

// Methods for getting the descriptors from their respective Luau tables.
WindowDescriptor getWindowDescriptor(lua_State* L);
ButtonDescriptor getButtonDescriptor(lua_State* L);
TextBoxDescriptor getTextBoxDescriptor(lua_State* L);

} // namespace Luwow::Gui