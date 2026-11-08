#include <gtest/gtest.h>
#include <MEGEngine/Core/Scene.hpp>
#include <MEGEngine/Core/ScriptedBehaviour.hpp>
#include <fixtures/Scene_fixture.hpp>


/**
 * Test Suite: Scene_fixture
 * Test Case: creatEntity_AddsToVector
 * 
 * When createEntity<Entity>() is called, an entity is added to the
 * entities vector
 */
TEST_F(Scene_fixture, createEntity_AddsToVector) {
    Scene scene;

    auto& entity = scene.createEntity<Entity>();
    const auto& entities = sceneEntities(scene);

    // Assert that entities vector contains 1 item
    ASSERT_EQ(entities.size(), 1u);

    // Expect entity in vector to have the same address as that returned by createEntity
    EXPECT_EQ(&entity,entities[0].get());
}


/**
 * Test Suite: Scene_fixture
 * Test Case: createCameraEntity_AddsToVector
 * 
 * When createEntity<Camera>() is called, a camera entity is added to the
 * entities vector
 */
TEST_F(Scene_fixture, createCameraEntity_AddsToVector) {
    Scene scene;

    auto& camera = scene.createEntity<Camera>(1, 1);
    const auto& entities = sceneEntities(scene);

    // Assert that entities vector contains 1 item
    ASSERT_EQ(entities.size(), 1u);

    // Expect entity in vector to have the same address as that returned by createEntity
    EXPECT_EQ(&camera,entities[0].get());
}


/**
 * Test Suite: Scene_fixture
 * Test Case: createCameraEntity_StoresRefToCamera
 * 
 * When createEntity<Camera>() is called, a reference to the camera is stored
 */
TEST_F(Scene_fixture, createCameraEntity_StoresRefToCamera) {
    Scene scene;

    auto& camera = scene.createEntity<Camera>(1, 1);

    EXPECT_EQ(&camera, &sceneCamera(scene));
    EXPECT_EQ(&camera, &scene.camera());
}


/**
 * Test Suite: Scene_fixture
 * Test Case: createCameraEntity_Fails_WhenViewportIsZero
 * 
 * When createEntity<Camera>() is called with any value of zero, exception is thrown
 */
TEST_F(Scene_fixture, createCameraEntity_Fails_WhenViewportIsZero) {
    Scene scene;

    EXPECT_ANY_THROW(scene.createEntity<Camera>(0, 1));
    EXPECT_ANY_THROW(scene.createEntity<Camera>(1, 0));
    EXPECT_ANY_THROW(scene.createEntity<Camera>(0, 0));
}


/**
 * Test Suite: Scene_fixture
 * Test Case: Update_Succeeds_WhenSceneIsEmpty
 * 
 * When update() is called and the scene is empty, the function passes
 */
TEST_F(Scene_fixture, Update_Succeeds_WhenSceneIsEmpty) {
    Scene scene;

    ASSERT_EXIT((scene.update(),exit(0)),::testing::ExitedWithCode(0),".*");
}


/**
 * Test Suite: Scene_fixture
 * Test Case: Update_Succeeds_WhenNoCameraInScene
 * 
 * When update() is called without a camera is in the scene, the
 * function should return no error
 */
TEST_F(Scene_fixture, Update_Succeeds_WhenNoCameraInScene) {
    Scene scene;

    scene.createEntity<Light_mock>();

    ASSERT_EXIT((scene.update(),exit(0)),::testing::ExitedWithCode(0),".*");
}

/**
 * Test Suite: Scene_fixture
 * Test Case: Update_RefreshesCamMatrix
 * 
 * When update() is called, the camera matrix is updated
 */
TEST_F(Scene_fixture, Update_RefreshesCamMatrix) {
    Scene scene;

    // Use mocked camera to check updateCamMatrix gets called
    ASSERT_TRUE(false);
}


/**
 * Test Suite: Scene_fixture
 * Test Case: Update_TriggersScriptBehaviour
 * 
 * When update() is called, the camera matrix is updated
 */
TEST_F(Scene_fixture, Update_TriggersScriptBehaviour) {
    Scene scene;

    // Use mocked ScriptedBehaviour to check onUpdate gets called
    ASSERT_TRUE(false);
}


/**
 * Test Suite: Scene_fixture
 * Test Case: Update_TriggersScriptBehaviour
 * 
 * When update() is called, the camera matrix is updated
 */
TEST_F(Scene_fixture, Update_RefreshesLightData) {
    Scene scene;

    // Get light data of empty scene
    // Add light to scene
    // Call update
    // Check light data has changed
    // Check light data is correct
    // Change values of light in scene
    // Call update
    // check light data has changed
    // check light data is correct
    ASSERT_TRUE(false);
}