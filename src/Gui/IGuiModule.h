#pragma once

#include "ILuauModule.h"
#include "Descriptors.h"
#include <string>
#include <vector>

// Abstract interface for the GUI API consistent across platform implementations
namespace Luwow::Gui {

class ICommandControl;

class IWindow {
public:
    virtual ~IWindow() = default;
    virtual void show() = 0;
    virtual uint16_t registerCommandControl(ICommandControl* commandControl) = 0;
    virtual ICommandControl* getCommandControl(uint16_t id) const = 0;
};

class ICommandControl {
public:
    virtual ~ICommandControl() = default;
    virtual void onCommand() = 0;
};

class IButton : public ICommandControl {
public:
    virtual ~IButton() = default;
};
    
    
// Interface for the GUI API consistent across platforms
class IGuiModule : public Luwow::Engine::ILuauModule {
public:
    virtual ~IGuiModule() = default;
    virtual IWindow* createWindow(const WindowDescriptor& descriptor) = 0;
    virtual IButton* createButton(const ButtonDescriptor& descriptor, IWindow* parent) = 0;
};

}