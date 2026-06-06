#include <thread>

#include "MEGEngine/Core/Application.h"
#include "MEGEngine/Core/engine.h"
#include "MEGEngine/Core/timer.h"
#include "MEGEngine/Core/scene.h"
#include "MEGEngine/Renderer/OpenGLRenderer.h"
#include "MEGEngine/Core/camera.h"
#include "MEGEngine/Core/settings.h"

#include "MEGEngine/Utils/log.h"


Application::Application(const ApplicationConfig& appConfig) {
	this->config = appConfig;
	
	Settings::instance().general().windowTitle = appConfig.windowTitle;
	Settings::instance().graphics().windowWidth = appConfig.width;
	Settings::instance().graphics().windowHeight = appConfig.height;
	Settings::instance().graphics().fullscreen = appConfig.fullscreen;
	Settings::instance().graphics().vsyncEnabled = appConfig.vsync;
}

Application::~Application() {
	if (running) shutdown();
}

void Application::run() {
	init();
	running = true;

	auto lastFrame = std::chrono::high_resolution_clock::now();

	while (running) {
		_scene->update();

		_renderer->render(*_scene);

		_window->display();
		_window->pollEvents();

		if (_window->shouldClose())
			requestQuit();

		// Limit FPS and set deltaTime
		uint32_t maxFps = Settings::instance().graphics().maxFps;
		if (!maxFps) {
			maxFps = 60;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000) / maxFps);

		Timer::setDeltaTime(lastFrame);
		onUpdate();
	}

	// close
	shutdown();

}

void Application::requestQuit() {
	running = false;
}

IWindow& Application::window() {
	return *_window;
}

Scene& Application::scene() {
	return *_scene;
}

IRenderer& Application::renderer() {
	return *_renderer;
}

void Application::init() {
	settings.init();

	//TODO: Pass window & renderer in either to constructor or init

	_window = std::make_unique<Window>();
	_window->create(config.windowTitle, config.width, config.height);

	_renderer = std::make_unique<OpenGLRenderer>(config.width, config.height);
	uint16_t status = _renderer->init();
	if (!status) {
		_window->terminate();
		LOG_ERR("Failed to initialise GLAD");
		exit(1);
	}

	// TODO: Set _scene with a loadScene func or similar
	_scene = std::make_unique<Scene>(config.width, config.height);

	Engine::instance().setApplication(this);

	onInit();
}

void Application::shutdown() {
	onShutdown();

	_scene = nullptr;
	_renderer = nullptr;
	_window = nullptr;
}
