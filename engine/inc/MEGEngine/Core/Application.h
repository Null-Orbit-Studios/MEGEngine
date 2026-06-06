#ifndef MEGENGINE_APPLICATION_H
#define MEGENGINE_APPLICATION_H

#include <memory>
#include <string>

#include "MEGEngine/common.h"
#include "MEGEngine/Core/scene.h"
#include "MEGEngine/Core/Interfaces/IWindow.h"
#include "MEGEngine/Core/Interfaces/IRenderer.h"

struct ENGINE_API ApplicationConfig {
	std::string windowTitle = "MEGEngine Game";
	int width = 1280;
	int height = 720;
	bool fullscreen = false;
	bool vsync = true;
};

class ENGINE_API Application {
public:
	ApplicationConfig config;

	explicit Application(const ApplicationConfig& config);
	Application() = default;
	virtual ~Application();

	
	// Prevents copying or moving of the instance

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) noexcept = default;
	Application& operator=(Application&&) noexcept = default;

	/**
     * @brief Contains the main application loop.
     * 
     * Initialises and then enters game loop. Updates scene, renderer, window,
     * polls for events, handles FPS limiting, calls onUpdate each loop.
     * 
     * @return void
     */
	void run();

	/**
     * @brief Exits the game loop.
     * 
     * Causes the game loop to stop at the end of the current loop
	 * and the application closes.
     * 
     * @return void
     */
	void requestQuit();

	/**
     * @brief Gets a reference to the application window.
     * 
     * @return IWindow& - Address of window object
     */
	IWindow& window();

	/**
     * @brief Gets a reference to the active scene.
     * 
     * @return IScene& - Address of scene object
     */
	Scene& scene();

	/**
     * @brief Gets a reference to the application renderer.
     * 
     * @return IRenderer& - Address of renderer object
     */
	IRenderer& renderer();

protected:
	/**
     * @brief Called once on application startup.
	 * 
	 * @return void
     */
	virtual void onInit() {}

	/**
     * @brief Called once per frame.
	 * 
	 * @return void
     */
	virtual void onUpdate() {};

	/**
     * @brief Called once on application shutdown.
	 * 
	 * @return void
     */
	virtual void onShutdown() {};

private:
	// Internal function to create necessary objects
	void init();
	// Internal function to handle application exit
	void shutdown();

	bool running = false;

	std::unique_ptr<IWindow> _window;
	std::unique_ptr<IRenderer> _renderer;
	std::unique_ptr<Scene> _scene;
};


#endif //MEGENGINE_APPLICATION_H