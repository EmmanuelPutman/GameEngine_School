#include "EP_Engine_PCH.h"
#include "InputManager.h"
#include <SDL.h>
//#include <iostream>

ep::InputManager::InputManager()
	:m_States{}
{
}

ep::InputManager::~InputManager()
{
	for (const std::pair<ControllerButton, Command*>& p : m_ControllerCommands)
	{
		delete p.second;
	}

	for (const std::pair<KeyboardKey, Command*>& p : m_KeyboardCommands)
	{
		delete p.second;
	}
}


//ONLY 1 CONTROLLER FOR THIS ENGINE
bool ep::InputManager::ProcessInput()
{
	// todo: read the input
	DWORD dwResult;
	// for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	// {
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected 
		// std::cout << "Controller connected\n";
		m_States[0] = state;
	}
	else
	{
		// Controller is not connected 
		//std::cout << "NO Controller connected\n";
	}
	// }


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

void ep::InputManager::HandleInput(const GameTime& gameTime)
{

	for (const std::pair<ControllerButton, Command*>& cmd : m_ControllerCommands)
	{
		if (IsPressed(cmd.first))
		{
			m_ControllerCommands[cmd.first]->Execute(gameTime);
			//return;
		}
	}


	for(const std::pair<KeyboardKey, Command*>& cmd : m_KeyboardCommands)
	{ 
		if (IsPressed(cmd.first))
		{ 
			m_KeyboardCommands[cmd.first]->Execute(gameTime);
			//return;
		}
	}
}

bool ep::InputManager::IsPressed(ControllerButton btnPressed) const
{
	// todo: return whether the given button is pressed or not.
	if (btnPressed == ControllerButton::ButtonA)
		return (m_States[0].Gamepad.wButtons == XINPUT_GAMEPAD_A) != 0;

	if (btnPressed == ControllerButton::ButtonB)
		return (m_States[0].Gamepad.wButtons == XINPUT_GAMEPAD_B) != 0;

	if (btnPressed == ControllerButton::ButtonX)
		return (m_States[0].Gamepad.wButtons == XINPUT_GAMEPAD_X) != 0;

	if (btnPressed == ControllerButton::ButtonY)
		return (m_States[0].Gamepad.wButtons == XINPUT_GAMEPAD_Y) != 0;

	return false;
}

bool ep::InputManager::IsPressed(KeyboardKey btnPressed) const
{
	if (btnPressed == KeyboardKey::KeyA)
		return GetAsyncKeyState('A') != 0;

	if (btnPressed == KeyboardKey::KeyS)
		return GetAsyncKeyState('S') != 0;

	if (btnPressed == KeyboardKey::KeyD)
		return GetAsyncKeyState('D') != 0;

	if (btnPressed == KeyboardKey::KeyW)
		return GetAsyncKeyState('W') != 0;

	if (btnPressed == KeyboardKey::KeySpace)
		return GetAsyncKeyState(VK_SPACE) != 0;

	return false;
}

void ep::InputManager::SetCommandToButton(ControllerButton button, Command* cmd)
{
	for(const std::pair<ControllerButton, Command*>& pair : m_ControllerCommands)
	{ 
		if (pair.first == button)
		{
			std::cout << "InputManager: Button already has a command!\n";
			delete cmd;
			cmd = nullptr;
			return;
		}
	}

	m_ControllerCommands.insert(std::pair<ControllerButton, Command*>(button, cmd));
}

void ep::InputManager::SetCommandToButton(KeyboardKey button, Command* cmd)
{
	for (const std::pair<KeyboardKey, Command*>& pair : m_KeyboardCommands)
	{
		if (pair.first == button)
		{
			std::cout << "InputManager: Button already has a command!\n";
			delete cmd;
			cmd = nullptr;
			return;
		}
	}

	m_KeyboardCommands.insert(std::pair<KeyboardKey, Command*>(button, cmd));
}
