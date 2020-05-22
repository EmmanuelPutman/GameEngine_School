#pragma once
#include <windows.h>
#include <Xinput.h>
#pragma comment(lib, "XINPUT9_1_0.LIB")
#include <vector>
#include "Command.h"
#include <map>

namespace ep
{

	enum class ControllerButton
	{
		ButtonA = 0,
		ButtonB = 1,
		ButtonX = 2,
		ButtonY = 3,
		//...
	};

	enum class KeyboardKey
	{
		KeyA = 0,
		KeyS = 1,
		KeyD = 2,
		KeyW = 3,
		KeySpace = 4,
		//...
	};


	class InputManager : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator= (const InputManager&) = delete;
		InputManager& operator= (const InputManager&&) = delete;

		bool ProcessInput();
		void HandleInput();
		bool IsPressed(ControllerButton btnPressed) const;
		bool IsPressed(KeyboardKey btnPressed) const;
		void SetCommandToButton(ControllerButton button, Command* cmd);
		void SetCommandToButton(KeyboardKey button, Command* cmd);

	private:
		XINPUT_STATE m_States[XUSER_MAX_COUNT];

		std::map<ControllerButton, Command*> m_ControllerCommands;
		std::map<KeyboardKey, Command*> m_KeyboardCommands;
	};
}