#include <gtest/gtest.h>
#include "MEGEngine/Core/Application.h"

TEST(ApplicationTests, ConstructorSetsConfigValues) {

    // config with non-default values
    ApplicationConfig config {
        .windowTitle = "Test",
        .width = 400,
        .height = 400,
        .fullscreen = true,
        .vsync = false
    };

    Application app(config);

    EXPECT_EQ(app.config.windowTitle, config.windowTitle);
    EXPECT_EQ(app.config.width, config.width);
    EXPECT_EQ(app.config.height, config.height);
    EXPECT_EQ(app.config.fullscreen, config.fullscreen);
    EXPECT_EQ(app.config.vsync, config.vsync);
}

TEST(ApplicationTests, InitialiseSuccessfully) {
    
}