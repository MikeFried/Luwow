local gui = require("gui.luau")

local window = gui.createWindow({
    Type = "Window",
    Title = "Luwow Created Window",
    Width = 400,
    Height = 300,
})

local _button = gui.createButton({
  Type = "Button",
  Caption = "Click me",
  OnPressed = function()
    print("Button pressed")
  end,
  Width = 100,
  Height = 30,
  Left = 40,
  Top = 40,
}, window)

window.show()
