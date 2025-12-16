-- This is the type system for the GUI API as it exists in C++ code.
export type CommonWindowDescriptor = {
    Left: number?,
    Top: number?,
    Width: number?,
    Height: number?,
}

export type WindowDescriptor = CommonWindowDescriptor & {
    Type: "Window",
    Title: string,
}

export type ButtonDescriptor = CommonWindowDescriptor & {
    Type: "Button",
    Caption: string,
    OnPressed: () -> (),
}

export type WindowDescriptors = WindowDescriptor | ButtonDescriptor

export type Window = {
    show: () -> boolean,
}

export type Button = {
}

export type Gui = {
    createWindow: (descriptor: WindowDescriptor) -> Window,
    createButton: (descriptor: ButtonDescriptor, parent: Window) -> Button,
}

return {} :: Gui