#include <filesystem>
#include <fstream>

#include "JSON/json.hpp"

#include "MEGEngine/Core/settings.h"
#include "MEGEngine/Utils/log.h"

using JSON = nlohmann::json;

Settings &Settings::instance() {
    static Settings instance;
    return instance;
}

void Settings::init() {
    LOG_DBG("Current directory: %s", std::filesystem::current_path().c_str());

    std::string settingsFilename = "defaultSettings.json";
    JSON json;
    std::ifstream file(settingsFilename, std::ios::binary);
    if (!file) {
        LOG_ERR("Failed to open settings file for reading: " +
                std::string(settingsFilename));
        throw std::runtime_error("Failed to read engine settings file");
    }
    std::stringstream ss;
    ss << file.rdbuf();
    json = JSON::parse(ss);

    // TODO: Handle exceptions when entry isn't found in json

    graphics().maxFps = json["Graphics"]["maxFps"];
    graphics().shaderDirectory =
        std::filesystem::path(MEGENGINE_RESOURCE_DIR) += "shaders";

    // TODO: get engine library location and store engine root directory

    _initialized = true;
}

bool Settings::isInitialized() { return _initialized; }

const GeneralSettings &Settings::general() const { return _general; }
GeneralSettings &Settings::general() { return _general; }

const GraphicsSettings &Settings::graphics() const { return _graphics; }
GraphicsSettings &Settings::graphics() { return _graphics; }
