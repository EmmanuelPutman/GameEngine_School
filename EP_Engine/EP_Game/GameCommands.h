#pragma once
#include "EP_Engine_PCH.h"

#include "Command.h"

#include "GameObject.h"

#include "TransformComponent.h"

enum class Commands
{
	Fire = 0,
	Duck = 1,
	Fart = 2,
	Jump = 3,
	MoveLeft = 4,
	//...
};

class EmptyCommand : public Command /* For command vector creation only */
{
public:
	void Execute(const GameTime&) override { std::cout << "NO COMMAND WAS ASSIGNED TO THIS BUTTON\n"; return; };
	virtual ~EmptyCommand() override = default;
};

class FireCommand : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fire);
		Logger::GetInstance().Log("Fire");
	};
	virtual ~FireCommand() override = default;
};

class DuckCommand : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Duck);
		Logger::GetInstance().Log("Duck");
	};

	~DuckCommand() override = default;
};

class JumpCommand : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Jump);

		Logger::GetInstance().Log("Jump");
	};
	~JumpCommand() override = default;
};

class FartCommand : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fart);
		Logger::GetInstance().Log("Fart");
	};
	~FartCommand() override = default;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(ep::GameObject* pCharacter) : m_pCharacter{ pCharacter } {}

	void Execute(const GameTime& gameTime) override
	{
		//Logger::GetInstance().Warning("Moving left");
		glm::vec3 currPos = m_pCharacter->GetComponent<TransformComponent>()->GetPosition();

		currPos.x -= 10.f * gameTime.elapsedSec;
		m_pCharacter->GetComponent<TransformComponent>()->ChangePositionTo(currPos.x, currPos.y, currPos.z);
	}

private:
	GameObject* m_pCharacter;
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(ep::GameObject* pCharacter) : m_pCharacter{ pCharacter } {}

	void Execute(const GameTime& gameTime) override
	{
		//Logger::GetInstance().Warning("Moving left");
		glm::vec3 currPos = m_pCharacter->GetComponent<TransformComponent>()->GetPosition();

		currPos.x += 10.f * gameTime.elapsedSec;
		m_pCharacter->GetComponent<TransformComponent>()->ChangePositionTo(currPos.x, currPos.y, currPos.z);
	}

private:
	GameObject* m_pCharacter;
};