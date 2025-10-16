#include "GuiModule.h"
#include "Engine.h"
#include "Window.h"
#include "Button.h"

#include "lua.h"
#include "lualib.h"
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

namespace Luwow::Gui {
using ILuauModule = Luwow::Engine::ILuauModule;
using Engine = Luwow::Engine::Engine;

// For all methods that require the Gui instance, we need to get it from the userdata.
static GuiModule* getModuleInstance(lua_State* L) {
    GuiModule* gui = static_cast<GuiModule*>(lua_touserdata(L, lua_upvalueindex(1)));
    if (!gui) {
        throw std::runtime_error("Gui module not found");
    }
    return gui;
}

GuiModule::GuiModule() : engine(nullptr) {}

ILuauModule* GuiModule::initialize(Engine* engine) {
    GuiModule* gui = new GuiModule();
    gui->setEngine(engine);
    return gui;
}

static Window* GetWindow(HWND hWnd) {
    return (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
        {
            Window* gui = GetWindow(hWnd);
            if (!gui) {
                throw std::runtime_error("Window not found");
            }
            uint16_t commandId = LOWORD(wParam);
            ICommandControl* commandControl = gui->getCommandControl(commandId);
            if (commandControl) {
                commandControl->onCommand();
            }
            break;
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/*static*/ void GuiModule::MessagePump() {
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void GuiModule::setEngine(Engine* engine) {
    this->engine = engine;

    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "LuwowWindow";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassExA(&wcex);
    engine->setMessagePumpCallback(MessagePump);
}

IWindow* GuiModule::createWindow(const WindowDescriptor& descriptor) {
    return new Window(descriptor);
}

IButton* GuiModule::createButton(const ButtonDescriptor& descriptor, IWindow* parent) {
    return new Button(descriptor, parent);
}

static int createWindow(lua_State* L) {
    GuiModule* gui = getModuleInstance(L);
    WindowDescriptor windowDescriptor = getWindowDescriptor(L);
    Window* window = static_cast<Window*>(gui->createWindow(windowDescriptor));
    getWindowTable(L, window);

    // Store the window pointer in the table for later retrieval
    lua_setreadonly(L, -1, 0);  // Make writable
    lua_pushlightuserdata(L, window);
    lua_setfield(L, -2, "__window_ptr");
    lua_setreadonly(L, -1, 1);  // Make readonly again
    return 1;
}

static int createButton(lua_State* L) {
    GuiModule* gui = getModuleInstance(L);
    ButtonDescriptor buttonDescriptor = getButtonDescriptor(L);
    
    // Get the parent window from the second parameter
    luaL_checktype(L, 2, LUA_TTABLE);
    lua_getfield(L, 2, "__window_ptr");
    Window* parent = static_cast<Window*>(lua_touserdata(L, -1));
    if (!parent) {
        luaL_error(L, "Parent window not found creating button.");
    }
    lua_pop(L, 1);  // Pop the window pointer from the stack
    
    Button* button = static_cast<Button*>(gui->createButton(buttonDescriptor, parent));
    getButtonTable(L, button);
    return 1;
}

const char* GuiModule::getModuleName() const {
    return "gui.luau";
}

static LuauExport exports[] = {
    { "createWindow", createWindow },
    { "createButton", createButton },
    { nullptr, nullptr }
};

const LuauExport* GuiModule::getExports() const {
    return exports;
}

} // namespace Luwow::Gui