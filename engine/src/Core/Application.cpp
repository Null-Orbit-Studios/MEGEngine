#include <thread>

#include "MEGEngine/Core/Application.h"
#include "MEGEngine/Core/engine.h"
#include "MEGEngine/Core/timer.h"
#include "MEGEngine/Core/scene.h"
#include "MEGEngine/Renderer/OpenGLRenderer.h"
#include "MEGEngine/Core/camera.h"
#include "MEGEngine/Core/settings.h"

#include "MEGEngine/Utils/log.h"

Application::~Application() {
	if (running) shutdown();
}

void Application::run() {
	init();
	running = true;

	auto lastFrame = std::chrono::high_resolution_clock::now();

	while (running) {
		if (_scene) {
			_scene->update();
			_renderer->render(*_scene);
		}

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

void Application::loadScene(std::shared_ptr<Scene> scene) {
	_scene = scene;
}

void Application::init() {
	settings.init();
	_window->create();

	uint16_t status = _renderer->init();
	if (!status) {
		_window->terminate();
		LOG_ERR("Failed to initialise GLAD");
		exit(1);
	}

	Engine::instance().setApplication(this);

	onInit();
}

void Application::shutdown() {
	onShutdown();

	_scene = nullptr;
	_renderer = nullptr;
	_window = nullptr;
}
