#include <memory>

#include "MEGEngine/Core.hpp"
#include "MEGEngine/Renderer.hpp"
#include "MEGEngine/Platform/Window.hpp"
#include "MEGEngine/Math/Quat.hpp"
#include "MEGEngine/Utils/Logger.hpp"

#include "CustomEvents.hpp"
#include "MoveCamera.hpp"

class ExampleGame : public Application {
public:
	using Application::Application;
	InputSystem inputSystem;

protected:
	void onInit() override {

		// create scene, add camera, and load scene
		auto _scene = std::make_shared<Scene>();
		_scene->createEntity<Camera>(settings.graphics().windowWidth, settings.graphics().windowHeight);
		loadScene(_scene);
		
		KeyboardDevice keyboard(&window());
		MouseDevice mouse(&window());
		inputSystem.manager().addDevice(std::make_unique<KeyboardDevice>(keyboard));
		inputSystem.manager().addDevice(std::make_unique<MouseDevice>(mouse));
		
		auto& move = inputSystem.createAction("Move", InputAction::Type::VEC2);
		auto& look = inputSystem.createAction("Look", InputAction::Type::VEC2);
		auto& captureMouse = inputSystem.createAction("CaptureMouse", InputAction::Type::BOOL);
		auto& escapeMouse = inputSystem.createAction("EscapeMouse", InputAction::Type::BOOL);
		auto& swapPlayer = inputSystem.createAction("SwapPlayer", InputAction::Type::BOOL);

		auto gameplay = inputSystem.createContext();
		inputSystem.bind(*gameplay, move, InputSource{InputSource::Type::KEY, KeyCode::W}, Vec2(0, 1));
		inputSystem.bind(*gameplay, move, InputSource{InputSource::Type::KEY, KeyCode::A}, Vec2(-1, 0));
		inputSystem.bind(*gameplay, move, InputSource{InputSource::Type::KEY, KeyCode::S}, Vec2(0, -1));
		inputSystem.bind(*gameplay, move, InputSource{InputSource::Type::KEY, KeyCode::D}, Vec2(1, 0));
		inputSystem.bind(*gameplay, swapPlayer, InputSource{InputSource::Type::KEY, KeyCode::T});
		inputSystem.bind(*gameplay, look, InputSource{InputSource::Type::MOUSE_DELTA});
		inputSystem.bind(*gameplay, captureMouse, InputSource{InputSource::Type::KEY, KeyCode::MOUSE_BUTTON_1});
		inputSystem.bind(*gameplay, escapeMouse, InputSource{InputSource::Type::KEY, KeyCode::ESCAPE});
		inputSystem.pushContext(gameplay);

		gameplay->linkActionCallback(
			"CaptureMouse",
			[this](const ActionState& s){
				setInputMode(window(), InputMode::CURSOR, InputModeValue::CURSOR_DISABLED);
			}
		);
		gameplay->linkActionCallback(
			"EscapeMouse",
			[this](const ActionState& s){
				setInputMode(window(), InputMode::CURSOR, InputModeValue::CURSOR_NORMAL);
			}
		);

		scene().camera().addComponent<MoveCamera>();

		if (auto ir = scene().camera().addComponent<InputReceiver>()) {
			ir->linkActionCallback(
				"Move",
				[this](const ActionState& s) { scene().camera().getComponent<MoveCamera>()->move(s.value().asVec2()); }
			);
			ir->linkActionCallback(
				"Look",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->look( s.value().asVec2()); }
			);

			PlayerController::instance().possess(scene().camera());
		}

		scene().camera().getComponent<Transform>()->setPosition({0, 0, -10});

		auto& light = scene().createEntity<Light>();
		light.setColour({1.0, 1.0, 1.0, 1.0});
		modelLoader.loadModelFromData(light, Cube::vertices(), Cube::indices());
		light.getComponent<MeshRenderer>()->setMaterial(std::make_shared<Material>(ShaderManager::getShader("light")));
		light.getComponent<MeshRenderer>()->material()->setColour({1.0, 1.0, 1.0, 1.0});

		auto& sword = scene().createEntity<Entity>();
		modelLoader.loadModelFromFile(sword, "/home/will/developer/proj/meg-engine/games/locomotion/models/sword/sword.gltf");
		sword.getComponent<Transform>()->setPosition(Vec3(5, -5, 0));
		sword.getComponent<Transform>()->setOrientation(Quat(0, 0, 0, 1));
		sword.getComponent<Transform>()->setScale(0.2);
		sword.addComponent<InputReceiver>();

		if (auto swordIr = sword.getComponent<InputReceiver>()) {
			auto camIr = scene().camera().getComponent<InputReceiver>();
			camIr->linkActionCallback(
				"SwapPlayer",
				[&](const ActionState& s){
					LOG_DBG("Possessing sword");
					PlayerController::instance().possess(sword);
				}
			);

			swordIr->linkActionCallback(
				"Move",
				[&](const ActionState& s){
					auto pos = sword.getComponent<Transform>()->position();
					sword.getComponent<Transform>()->setPosition({pos.x + s.value().asVec2().x, pos.y, pos.z + s.value().asVec2().y});
				}
			);
		}

		auto& floor = scene().createEntity<Entity>();
		modelLoader.loadModelFromData(floor, Cube::vertices(), Cube::indices());
		floor.getComponent<MeshRenderer>()->setMaterial(std::make_shared<Material>());
		floor.getComponent<Transform>()->setPosition(Vec3(0, -30, 0));
		floor.getComponent<Transform>()->setScale(Vec3(100, 0.1, 100));

	}

	void onUpdate() override {
		// once per frame
		EventManager::processEvents();
		inputSystem.update();
	}
};

int main() {
	ApplicationConfig appConfig;
	appConfig = {
		.windowTitle = "Test Game",
		.width = 1280,
		.height = 720
	};

	auto renderer = std::make_unique<OpenGLRenderer>(appConfig.width, appConfig.height);
	auto window = std::make_unique<Window>(appConfig.windowTitle, appConfig.width, appConfig.height);

	ExampleGame game(std::move(renderer), std::move(window));
	game.run();

    return 0;
}