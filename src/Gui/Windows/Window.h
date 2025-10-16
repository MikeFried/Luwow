#pragma once

#include "IGuiModule.h"
#include <vector>
#include <windows.h>
#include <unordered_map>

namespace Luwow::Gui {

class Window : public IWindow {
public:
    Window(const WindowDescriptor& descriptor);
    ~Window();
    virtual void show() override;
    virtual uint16_t registerCommandControl(ICommandControl* commandControl) override;
    virtual ICommandControl* getCommandControl(uint16_t id) const override;

    // Accessors
    WindowDescriptor getDescriptor() const { return descriptor; };
    HWND getHWND() const { return hWnd; };

private:
    uint16_t nextCommandId = 1;
    std::unordered_map<uint16_t, ICommandControl*> commandControls;
    WindowDescriptor descriptor;
    HWND hWnd;
};

void getWindowTable(lua_State* L, Window* window);

} // namespace Luwow::Gui