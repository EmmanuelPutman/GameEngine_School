#pragma once
#include "EP_Engine_PCH.h"

#include "Command.h"

#include "GameObject.h"
#include "Character.h"
#include "BubbleSpawner.h"

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

class FireTest : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fire);
		Logger::GetInstance().Log("Fire");
	};
	virtual ~FireTest() override = default;
};

class DuckTest : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Duck);
		Logger::GetInstance().Log("Duck");
	};

	~DuckTest() override = default;
};

class JumpTest : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Jump);

		Logger::GetInstance().Log("Jump");
	};
	~JumpTest() override = default;
};

class FartTest : public Command
{
public:
	void Execute(const GameTime&) override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fart);
		Logger::GetInstance().Log("Fart");
	};
	~FartTest() override = default;
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(Character* pCharacter) : m_pCharacter{ pCharacter } {}

	void Execute(const GameTime&) override
	{
		float xVel = -1.f;
		m_pCharacter->SetVelocity(true, xVel);
		m_pCharacter->SetLookDirection(-1);
	}

private:
	Character* m_pCharacter;
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(Character* pCharacter) : m_pCharacter{ pCharacter } {}

	void Execute(const GameTime&) override
	{
		float xVel = 1.f;
		m_pCharacter->SetVelocity(true, xVel);
		m_pCharacter->SetLookDirection(1);
	}

private:
	Character* m_pCharacter;
};

class JumpCommand : public Command
{
public:
	JumpCommand(Character* pCharacter) : m_pCharacter{ pCharacter } {}

	void Execute(const GameTime&) override
	{
		if (m_pCharacter->GetVelocity().y >= 0.f)
		{
			if (m_pCharacter->IsGrounded())
			{
				float yVel = -1.f;
				m_pCharacter->SetVelocity(false, yVel);
				m_pCharacter->SetJumping(true);
			}
		}
	}

private:
	Character* m_pCharacter;
};

class ShootCommand : public Command
{
public:
	ShootCommand(Character* pCharacter, BubbleSpawner* pBubbleSpawner) 
		: m_pCharacter{ pCharacter }
		, m_pBubbleSpawner{ pBubbleSpawner }
	{}

	void Execute(const GameTime&) override
	{
		m_pCharacter->SetState(Character::State::Attacking);
		m_pBubbleSpawner->ShootBubble(m_pCharacter->GetLookDirection(), m_pCharacter->GetComponent<TransformComponent>()->GetPosition());
	}

private:
	Character* m_pCharacter;
	BubbleSpawner* m_pBubbleSpawner;
};