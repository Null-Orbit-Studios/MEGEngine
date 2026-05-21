#include <fstream>
#include <filesystem>

#include "JSON/json.hpp"

#include "MEGEngine/utils/log.h"
#include "MEGEngine/settings.h"

using JSON = nlohmann::json;

namespace MEGEngine {

    Settings& Settings::instance() {
        static Settings instance;
        return instance;
    }

    void Settings::init() {
        Log(LogLevel::DBG, "Current directory: %s", std::filesystem::current_path().c_str());


        std::string settingsFilename = "defaultSettings.json";
        JSON json;
        std::ifstream file(settingsFilename, std::ios::binary);
        if (!file) {
            Log(LogLevel::ERR, "Failed to open settings file for reading: " + std::string(settingsFilename));
            throw std::runtime_error("Failed to read engine settings file");
        }
        std::stringstream ss;
        ss << file.rdbuf();
        json = JSON::parse(ss);

        // TODO: Handle exceptions when entry isn't found in json

        general().shaderDirectory = json["General"]["shaderDirectory"];
        general().modelDirectory = json["General"]["modelDirectory"];

        graphics().maxFps = json["Graphics"]["maxFps"];

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