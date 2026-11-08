#include <MEGEngine/Core/Scene.hpp>

#include <mocks/Light_mock.hpp>
#include <mocks/Camera_mock.hpp>

class Scene_fixture : public ::testing::Test {
protected:
    // Access scene private variables
    std::vector<std::unique_ptr<Entity>>& sceneEntities(Scene& s) { return s._entities; }
    Camera& sceneCamera(Scene& s) { return *s._camera; }

    void SetUp() override {

    }

    void TearDown() override {

    }    
};