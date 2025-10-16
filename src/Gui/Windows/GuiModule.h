#pragma once
#include "IGuiModule.h"
#include "Engine.h"

namespace Luwow::Gui {

using Engine = Luwow::Engine::Engine;

class GuiModule : public IGuiModule {
public:
    GuiModule();
    ~GuiModule() = default;

    const char* getModuleName() const override;
    const LuauExport* getExports() const override;
    ILuauModule* initialize(Engine* engine) override;
    IWindow* createWindow(const WindowDescriptor& descriptor) override;
    IButton* createButton(const ButtonDescriptor& descriptor, IWindow* parent) override;
    static void MessagePump();

private:
    void setEngine(Engine* engine);
    Engine* engine;
};

} // namespace Luwow::Gui