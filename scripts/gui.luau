--! @meta
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
    OnPressed: () -> boolean,
}

export type TextBoxDescriptor = CommonWindowDescriptor & {
    Type: "TextBox",
    Text: string,
    MultiLineMode: boolean,
    Font: string,
}

export type WindowDescriptors = WindowDescriptor | ButtonDescriptor | TextBoxDescriptor

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