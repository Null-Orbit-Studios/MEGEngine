#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

#include "MEGEngine/common.h"

struct ENGINE_API GeneralSettings {
std::string shaderDirectory;
std::string modelDirectory;
std::string windowTitle;
};

struct ENGINE_API GraphicsSettings {
uint32_t maxFps;
uint32_t windowWidth;
uint32_t windowHeight;
bool fullscreen;
bool vsyncEnabled;
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


private: // private first for the struct definitions
	Settings() = default;
	bool _initialized = false;

	GeneralSettings _general;
	GraphicsSettings _graphics;

};

inline ENGINE_API Settings& settings = Settings::instance();




#endif //SETTINGS_H