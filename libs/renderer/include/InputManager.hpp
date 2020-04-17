#pragma once

#include <map>
#include <set>
#include <utility>

#include <GLFW/glfw3.h>

#include "InputData.hpp"

class InputManager
{
public:
	InputManager();
	~InputManager();
	void AddKey(int key, int mods);
	void AddButton(int mouse_button, int mods);
	bool AddGamepad(int gamepadId);
	void AddGamepadAxis(int gamepadId, int gamepadAxis);
	void AddGamepadButton(int gamepadId, int gamepadButton);

	void UpdateKey(int key, int action, int mods);

	void SetCursorTracking(int isTracked);
	void SetScrollTracking(int isTracked);

	void RemoveKey(int key, int mods);
	void RemoveButton(int mouse_button, int mods);
	bool RemoveGamepad(int gamepadId);
	void RemoveGamepadAxis(int gamepadId, int gamepadAxis);
	void RemoveGamepadButton(int gamepadId, int gamepadButton);

	InputData Update(GLFWwindow* window);

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
	std::map<std::pair<int, int>, std::pair<int,int>> keyValues{};

	// MOUSE //

	// mouse buttons added to tracking
	std::set<std::pair<int, int>> trackedButtons{};

	bool isMouseCursorTracked = false;
	bool isMouseScrollTracked = false;

	// GAMEPADS //

	// glfw ids of gamepads connected
	// updates on gamepad_callback disconnected i connected
	std::set<int> conectedGamepads{};

	// first int to gamepad id, set to set osi/przycisków pada
	// każdy pad może mieć inne mapowanie, stąd ten podział
	std::map<int, std::set<int>> trackedGamepadAxes{};
	std::map<int, std::set<int>> trackedGamepadButtons{};
};
