#ifndef MEGENGINE_IWINDOW_H
#define MEGENGINE_IWINDOW_H

class IWindow {
protected:
    struct WindowHandle;
    struct Impl;

public:
    virtual ~IWindow() {};

    virtual void create(const std::string& title, int width, int height) = 0;
    virtual void pollEvents() = 0;
    virtual bool shouldClose() const = 0;
    virtual void display() = 0;
    virtual void terminate() = 0;

    virtual Impl& impl() = 0;
    virtual WindowHandle& handle() = 0;

};

#endif