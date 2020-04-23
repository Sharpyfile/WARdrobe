#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <utility>

#include <GLFW/glfw3.h>

#include "Enums.h"
#include "Input.hpp"

typedef std::function<void()>     Callback;
typedef std::shared_ptr<Callback> CallbackPointer;

class InputManager
{
public:
	InputManager();
	~InputManager();
	void AddKey(int key, int mods);
	void AddButton(int mouse_button, int mods);
	void AddGamepad(int gamepadId);
	void AddGamepadAxis(int gamepadId, int gamepadAxis);
	void AddGamepadButton(int gamepadId, int gamepadButton);

	void UpdateKey(int key, int action, int mods);
	void UpdateButton(int button, int action, int mods);
	void UpdateGamepad(int jid);

	void SetCursorTracking(int isTracked);
	void SetScrollTracking(int isTracked);

	void RemoveKey(int key, int mods);
	void RemoveButton(int mouse_button, int mods);
	void RemoveGamepad(int gamepadId);
	void RemoveGamepadAxis(int gamepadId, int gamepadAxis);
	void RemoveGamepadButton(int gamepadId, int gamepadButton);

	void Update(GLFWwindow* window);

	////

	void AddInput(int id, int source)
	{

		Input input;
		input.id = id;
		input.source = source;
		input.state = InputState::IDLE;
		input.mods = 0;

		inputs.push_back(input);

		std::cout << "Input " << input.id << " from " << input.source
		          << " added!\n";
	}

	void BindAction(int             id,
	                int             source,
	                int             state,
	                int             mods,
	                CallbackPointer callbackPtr)
	{
		Input input;
		input.id = id;
		input.source = source;
		input.state = state;
		input.mods = mods;

		//(*callbackPtr)();
		// std::cout << typeid(callbackPtr).name() << std::endl;

		bindings.insert(std::make_pair(input, callbackPtr));
	}

	void UpdateInput(int id, int source, int state, int mods)
	{

		Input input;
		input.id = id;
		input.source = source;
		input.state = -1;
		input.mods = -1;

		std::list<Input>::iterator it =
		  std::find(inputs.begin(), inputs.end(), input);

		if (it != inputs.end()) {
			std::cout << "Input " << (&input)->id << " from " << (&input)->source
			          << " updated!\n";
		}
	}

	void Call()
	{
		for (auto input : inputs) {
			auto it = bindings.find(input);

			if (it != bindings.end()) {
				std::cout << "Callback binded to input " << (&input)->id
				          << " from source " << (&input)->source << " called!\n";
				(*it->second)();
			}
		}
	}

private:
	// KEYBOARD //

	// keyboard keys added to tracking
	std::set<std::pair<int, int>> trackedKeys{};

	// TODO: Change to bitmask
	// KEY STATE MASK
	// <0,0> IDLE    0x0
	// <0,1> PRESSED 0x1
	// <1,0> RELEASE 0x2
	// <1,1> REPEAT  0x3
	std::map<std::pair<int, int>, std::pair<int, int>> keyValues{};

	// MOUSE //

	// mouse buttons added to tracking
	std::set<std::pair<int, int>>                      trackedButtons{};
	std::map<std::pair<int, int>, std::pair<int, int>> buttonValues{};

	bool isMouseCursorTracked = false;
	bool isMouseScrollTracked = false;

	bool isMouseButtonHoldDown[5] = { false, false, false, false, false };

	// GAMEPADS //

	// glfw ids of gamepads connected
	// updates on gamepad_callback disconnected i connected
	std::set<int> conectedGamepads{};

	// first int to gamepad id, set to set osi/przycisków pada
	// każdy pad może mieć inne mapowanie, stąd ten podział
	std::map<int, std::set<int>> trackedGamepadAxes{};
	std::map<int, std::set<int>> trackedGamepadButtons{};

	////

	// the desired state of the input and the callback to fire
	std::map<Input, CallbackPointer> bindings;
	// current state of the inputs
	std::list<Input> inputs;
};
