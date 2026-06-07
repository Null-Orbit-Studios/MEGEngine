#ifndef MEGENGINEPROJECT_WINDOW_H
#define MEGENGINEPROJECT_WINDOW_H

#include <string>

#include "MEGEngine/common.h"
#include "MEGEngine/Core/Interfaces/IWindow.h"


class ENGINE_API Window : public IWindow {
public:
    Window(std::string title, uint32_t width, uint32_t height);
    ~Window();

    // Prevents copying of the instance
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    /**
     * @brief Create and display a blank window
     * 
     * Creates a blank window using the width, height and title it was
     * constructed with
     * 
     * @return void
     */
    void create() override;

    /**
     * @brief Checks for and registers events that need to be processed
     * 
     * Detects inputs or events of any kind. Sets flags that can indicate
     * whether should close etc.
     * 
     * @return void
     */
    void pollEvents() override;

    /**
     * @brief Checks if an action has happened that should cause the application to close
     * 
     * @returns bool
     * @retval True - Window should close
     * @retval False - Window does not need to close
     */
    bool shouldClose() const override;

    /**
     * @brief Display what has been rendered on the window
     * 
     * @return void
     */
    void display() override;

    /**
     * @brief Terminate the window and destroy all stored objects.
     * 
     * @return void
     */
    void terminate() override;

    /**
     * @brief DEPRECATED - USE `handle()` INSTEAD
     * 
     * Get the real implementation object of the window
     * 
     * @return Structure containing handle pointer to window object
     */
    Impl& impl() override;

    /**
     * @brief Get the real implementation object of the window
     * 
     * @return Handle structure containing pointer to window object
     */
    WindowHandle& handle() override;

private:
    // Private wrapper for GLFWwindow to keep it hidden from public headers
    Impl* _impl;
    WindowHandle* _handle;

    std::string _windowTitle;
    uint32_t _width;
    uint32_t _height;
};


#endif //MEGENGINEPROJECT_WINDOW_H