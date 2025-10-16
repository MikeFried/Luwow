#pragma once

#include "IGuiModule.h"
#include <windows.h>

namespace Luwow::Gui {

class Button : public IButton {
public:
    Button(const ButtonDescriptor& descriptor, IWindow* parent);
    ~Button();

    virtual void onCommand() override;

private:
    ButtonDescriptor descriptor;
    HWND hButton;
};

void getButtonTable(lua_State* L, Button* button);

} // namespace Luwow::Gui