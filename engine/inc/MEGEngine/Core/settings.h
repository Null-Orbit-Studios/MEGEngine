#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "MEGEngine/common.h"

struct ENGINE_API GeneralSettings {
std::string shaderDirectory = "";
std::string windowTitle = "MEGEngine Game";
};

struct ENGINE_API GraphicsSettings {
uint32_t maxFps = 60;
uint32_t windowWidth = 1280;
uint32_t windowHeight = 720;
bool fullscreen = false;
bool vsyncEnabled = true;
};


class ENGINE_API Settings {
public:
	static Settings& instance();
	void init();
	bool isInitialized();

	const GeneralSettings& general() const;
	GeneralSettings& general();

	const GraphicsSettings& graphics() const;
	GraphicsSettings& graphics();


private:
	Settings() = default;
	bool _initialized = false;

	GeneralSettings _general;
	GraphicsSettings _graphics;

};

inline ENGINE_API Settings& settings = Settings::instance();




#endif //SETTINGS_H