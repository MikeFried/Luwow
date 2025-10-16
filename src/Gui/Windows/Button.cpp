#include <windows.h>
#include "Button.h"
#include "Window.h"
#include <iostream>
#include <stdexcept>
#include "lua.h"
#include "lualib.h"

namespace Luwow::Gui {

Button::Button(const ButtonDescriptor& descriptor, IWindow* parent) : descriptor(descriptor), hButton(nullptr) {
    Window* parentWindow = dynamic_cast<Window*>(parent);
    if (!parentWindow) {
        throw std::runtime_error("Parent window is not a Window");
    }

    uint16_t id = parentWindow->registerCommandControl(this);

    HWND hParent = parentWindow->getHWND();
    hButton = CreateWindowExA(
        0,
        "BUTTON",  // Predefined class; Unicode assumed 
        descriptor.Caption.c_str(),      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        descriptor.Left,
        descriptor.Top,
        descriptor.Width,
        descriptor.Height,
        hParent,
        (HMENU) id,
        (HINSTANCE)GetWindowLongPtr(hParent, GWLP_HINSTANCE),
        NULL
    );
    SetWindowLongPtr(hButton, GWLP_USERDATA, (LONG_PTR)this);
}

Button::~Button() {
    // // Clean up the Lua callback reference
    // if (descriptor.OnPressedRef != LUA_NOREF && descriptor.L != nullptr) {
    //     lua_unref(descriptor.L, LUA_REGISTRYINDEX);
    // }
}

void Button::onCommand() {
    lua_State* L = descriptor.L;
    // call the callback in Descriptor.OnPressedRef with pcall
    lua_getref(L, descriptor.OnPressedRef);
    lua_pcall(L, 0, 0, 0);
}

void getButtonTable(lua_State* L, Button* button) {
    lua_createtable(L, 0, 0);
    lua_pushlightuserdata(L, button);
    lua_setfield(L, -2, "button");
    lua_setreadonly(L, -1, 1);
}

} // namespace Luwow::Gui