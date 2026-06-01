#include <memory>

#include "MEGEngine.h"
#include "MEGEngine/Math/quat.h"
#include "MEGEngine/utils/log.h"

#include "CustomEvents.h"
#include "MoveCamera.h"

class ExampleGame : public Application {
public:
	using Application::Application;
	InputSystem inputSystem;

protected:
	void onInit() override {
		// once at start
		inputSystem.init();
		Engine::instance().setInputSystem(&inputSystem); // for access throughout the application
		KeyboardDevice keyboard(&window());
		MouseDevice mouse(&window());
		inputSystem.manager().addDevice(std::make_unique<KeyboardDevice>(keyboard));
		inputSystem.manager().addDevice(std::make_unique<MouseDevice>(mouse));
		// TODO: Have a single move action that takes a Vec2 or Vec3?
		auto& moveFwd = inputSystem.createAction("MoveForward", InputAction::Type::FLOAT);
		auto& moveBwd = inputSystem.createAction("MoveBackward", InputAction::Type::FLOAT);
		auto& moveRgt = inputSystem.createAction("MoveRight", InputAction::Type::FLOAT);
		auto& moveLft = inputSystem.createAction("MoveLeft", InputAction::Type::FLOAT);
		auto& swapPlayer = inputSystem.createAction("SwapPlayer", InputAction::Type::BOOL);
		auto& look = inputSystem.createAction("Look", InputAction::Type::VEC2);
		auto& captureMouse = inputSystem.createAction("CaptureMouse", InputAction::Type::BOOL);
		auto& escapeMouse = inputSystem.createAction("EscapeMouse", InputAction::Type::BOOL);
		auto gameplay = inputSystem.createContext();
		inputSystem.bind(*gameplay, moveFwd, InputSource{InputSource::Type::KEY, KeyCode::W}, +1);
		inputSystem.bind(*gameplay, moveLft, InputSource{InputSource::Type::KEY, KeyCode::A}, -1);
		inputSystem.bind(*gameplay, moveBwd, InputSource{InputSource::Type::KEY, KeyCode::S}, -1);
		inputSystem.bind(*gameplay, moveRgt, InputSource{InputSource::Type::KEY, KeyCode::D}, +1);
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
				"MoveForward",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->moveForward(s.value.asFloat()); }
			);
			ir->linkActionCallback(
				"MoveBackward",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->moveForward(s.value.asFloat()); }
			);
			ir->linkActionCallback(
				"MoveRight",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->moveRight(s.value.asFloat()); }
			);
			ir->linkActionCallback(
				"MoveLeft",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->moveRight(s.value.asFloat()); }
			);
			ir->linkActionCallback(
				"Look",
				[this](const ActionState& s){ scene().camera().getComponent<MoveCamera>()->look( s.value.asVec2()); }
			);

			Engine::instance().playerController()->possess(scene().camera());
		}

		scene().camera().getComponent<Transform>()->setPosition({0, 0, -10});

		auto& light = scene().createEntity<Light>();
		light.setColour({1.0, 1.0, 1.0, 1.0});
		modelLoader.loadModelFromData(light, Cube::vertices(), Cube::indices());
		light.getComponent<MeshRenderer>()->setMaterial(std::make_shared<Material>(ShaderManager::getShader("light")));
		light.getComponent<MeshRenderer>()->material()->setColour({1.0, 1.0, 1.0, 1.0});

		auto& sword = scene().createEntity<Entity>();
		modelLoader.loadModelFromFile(sword, "/home/will/developer/proj/meg-engine/examples/locomotion/models/sword/sword.gltf");
		sword.getComponent<Transform>()->setPosition(Vec3(5, -5, 0));
		sword.getComponent<Transform>()->setOrientation(Quat(0, 0, 0, 1));
		sword.getComponent<Transform>()->setScale(0.2);
		sword.addComponent<InputReceiver>();

		if (auto swordIr = sword.getComponent<InputReceiver>()) {
			auto camIr = scene().camera().getComponent<InputReceiver>();
			camIr->linkActionCallback(
				"SwapPlayer",
				[&](const ActionState& s){
					Log(LogLevel::DBG, "Possessing sword");
					Engine::instance().playerController()->possess(sword);
				}
			);

			swordIr->linkActionCallback(
				"MoveForward",
				[&](const ActionState& s){
					Log(LogLevel::DBG, "Moving Sword forward");
					auto pos = sword.getComponent<Transform>()->position();
					sword.getComponent<Transform>()->setPosition({pos.x, pos.y, pos.z + s.value.asFloat()});
				}
			);

			swordIr->linkActionCallback(
				"MoveBackward",
				[&](const ActionState& s){
					Log(LogLevel::DBG, "Moving Sword backward");
					auto pos = sword.getComponent<Transform>()->position();
					sword.getComponent<Transform>()->setPosition({pos.x, pos.y, pos.z + s.value.asFloat()});
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

	ExampleGame game(appConfig);
	game.run();

    return 0;
}