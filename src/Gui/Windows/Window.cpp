#include "Window.h"
#include <iostream>
#include <string>
#include "lua.h"
#include "lualib.h"

namespace Luwow::Gui {

Window::Window(const WindowDescriptor& descriptor) : descriptor(descriptor) {
    hWnd = CreateWindowExA(
        WS_EX_CLIENTEDGE,
        "LuwowWindow",
        descriptor.Title.c_str(),
        WS_OVERLAPPEDWINDOW,
        descriptor.Left,
        descriptor.Top,
        descriptor.Width,
        descriptor.Height,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (hWnd == NULL) {
        throw std::runtime_error("Failed to create window");
    }

    SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);
}

static int show(lua_State* L) {
    Window* window = static_cast<Window*>(lua_touserdata(L, lua_upvalueindex(1)));
    if (!window) {
        throw std::runtime_error("Window not found");
    }
    window->show();
    return 0;
}

uint16_t Window::registerCommandControl(ICommandControl* commandControl) {
    uint16_t id = nextCommandId++;
    commandControls[id] = commandControl;
    return id;
}

ICommandControl* Window::getCommandControl(uint16_t id) const {
    return commandControls.at(id);
}

void Window::show() {
    ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
    //DestroyWindow(hWnd);
}

void getWindowTable(lua_State* L, Window* window) {
    lua_createtable(L, 0, 2);
    lua_pushlightuserdata(L, window);
    lua_pushcclosure(L, &show, "show", 1);
    lua_setfield(L, -2, "show");
    lua_setreadonly(L, -1, 1);
}

} // namespace Luwow::Gui