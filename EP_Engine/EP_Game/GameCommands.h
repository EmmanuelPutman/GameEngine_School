#pragma once
#include "EP_Engine_PCH.h"

#include "Command.h"

#include "GameObject.h"
#include "Character.h"
#include "BubbleSpawner.h"

#include "TransformComponent.h"
#include "AnimationComponent.h"

enum class Commands
{
	FireBubble,
	Jump,
	//...
};

class EmptyCommand : public Command /* For command vector creation only */
{
public:
	void Execute(const GameTime&) override { std::cout << "NO COMMAND WAS ASSIGNED TO THIS BUTTON\n"; return; };
	virtual ~EmptyCommand() override = default;
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
		m_pCharacter->GetComponent<AnimationComponent>()->SetDirection(-1);
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
		m_pCharacter->GetComponent<AnimationComponent>()->SetDirection(1);
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
				ServiceLocator::GetAudio().PlaySounds((int)Commands::Jump);
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
		ServiceLocator::GetAudio().PlaySounds((int)Commands::FireBubble);
		m_pCharacter->SetState(Character::State::Attacking);
		m_pBubbleSpawner->ShootBubble(m_pCharacter->GetLookDirection(), m_pCharacter->GetComponent<TransformComponent>()->GetPosition());
	}

private:
	Character* m_pCharacter;
	BubbleSpawner* m_pBubbleSpawner;
};