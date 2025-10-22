target_sources(Luwow.Engine PRIVATE
    src/engine/Engine.cpp
    src/engine/Engine.h
    src/engine/ILuauModule.h
    src/engine/Package.cpp
    src/engine/Package.h
)

target_sources(Luwow.Gui PRIVATE
    src/gui/Descriptors.cpp
    src/gui/Descriptors.h
    src/gui/IGuiModule.h
    src/gui/Windows/Button.cpp
    src/gui/Windows/Button.h
    src/gui/Windows/GuiModule.cpp
    src/gui/Windows/GuiModule.h
    src/gui/Windows/Window.cpp
    src/gui/Windows/Window.h
)

target_sources(Luwow.LCompile PRIVATE
    src/lcompile/main.cpp
    src/lcompile/LuauCompiler.cpp
    src/lcompile/LuauCompiler.h
)

target_sources(Luwow.LRun PRIVATE
    src/lrun/main.cpp
)

target_sources(Luwow.LDebug PRIVATE
    src/ldebug/main.cpp
)
