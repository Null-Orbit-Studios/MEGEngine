#include "mINI/ini.h"

#include "MEGEngine/utils/log.h"
#include "MEGEngine/settings.h"
#include <filesystem>

using namespace mINI;

namespace MEGEngine {

    Settings& Settings::instance() {
        static Settings instance;
        return instance;
    }

    void Settings::init() {
        INIFile file("../engine/engineSettings.ini");
        INIStructure ini;
        Log(LogLevel::DBG, "Current directory: %s", std::filesystem::current_path().c_str());
        bool readSuccess = file.read(ini);
        if (!readSuccess) {
            Log(LogLevel::ERR, "Failed to read engine settings file");
            throw std::runtime_error("Failed to read engine settings file");
        }

        general().shaderDirectory = ini.get("General").get("shaderDirectory");
        general().modelDirectory = ini.get("General").get("modelDirectory");

        graphics().maxFps = stoi(ini.get("Graphics").get("maxFps"));

        //TODO: get engine library location and store engine root directory

        _initialized = true;
    }

    bool Settings::isInitialized() {
        return _initialized;
    }

    const GeneralSettings& Settings::general() const {
        return _general;
    }
    GeneralSettings& Settings::general() {
        return _general;
    }

    const GraphicsSettings& Settings::graphics() const {
        return _graphics;
    }
    GraphicsSettings& Settings::graphics() {
        return _graphics;
    }
}