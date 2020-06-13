#include "EP_Engine_PCH.h"
#include "PlayerCharacter.h"

#include "InputManager.h"
#include "GameCommands.h"
#include "SceneManager.h"
#include "Scene.h"

#include "BubbleSpawner.h"

#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"

PlayerCharacter::PlayerCharacter(float moveSpeed)
	:Character(moveSpeed, 4, 1, "CharacterRun.png", 7, 1, 0.09f)
	, m_IsInvulnerable{ true }
	, m_InvulnerableTimer{ false }
	, m_PreviousHealth{ 4 }
	, m_TimeInvulnerable{ 2.f }
{
	//Add the BubbleSpawner
	m_pBubbleSpawner = new BubbleSpawner();

	//Set the different states
	StateSettings walking{ "CharacterRun.png", State::Moving, 7, 1, 0.09f };
	StateSettings attacking{ "CharacterAttack.png", State::Attacking, 8, 1, 0.25f };
	m_StateSettings.push_back(walking);
	m_StateSettings.push_back(attacking);

	//Set the collision callback for the left and right
	auto collisionXCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (static_cast<Character*>(pThis)->IsJumping())
			return;

		if (pOther != pThis && pOther != nullptr)
		{
			if (pOther->GetTag() == "Block")
			{
				if (static_cast<Character*>(pThis)->GetVelocity().x > 0.f)
				{
					//Logger::GetInstance().Log("Right side was hit");
					glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
					pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x - pOther->GetWidth() / 2 - pThis->GetWidth() / 2 - 4;
					if (pos.x > 46.f)
					{
						pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
					}
				}
				else if (static_cast<Character*>(pThis)->GetVelocity().x < 0.f)
				{
					//Logger::GetInstance().Log("Left side was hit");
					glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
					pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x + pOther->GetWidth() / 2 + pThis->GetWidth() / 2 + 4;
					if (pos.x < 600.f)
					{
						pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
					}
				}
			}

			if (pOther->GetTag() == "Enemy" && static_cast<Character*>(pOther)->GetState() == Character::State::Bubbled)
			{
				pOther->GetComponent<HealthComponent>()->TakeDamage(static_cast<Character*>(pThis)->GetDamage());
			}
		}
	};

	m_pWidthCollider->SetCollisionCallBack(collisionXCallBack);


	//Set the collision callback for the top and bottom
	auto collisionYCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (static_cast<Character*>(pThis)->IsJumping())
			return;
		if (pOther != pThis && pOther != nullptr && pOther->GetTag() == "Block")
		{
			if (static_cast<Character*>(pThis)->GetVelocity().y > 0.f)
			{
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.y = pOther->GetComponent<TransformComponent>()->GetPosition().y - pOther->GetHeight() / 2 - pThis->GetHeight() / 2 - 2;
				if (pos.y > 40.f)
				{
					pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
					static_cast<Character*>(pThis)->SetVelocity(false, 0.f);
				}
			}
			else if (static_cast<Character*>(pThis)->GetVelocity().y < 0.f)
			{
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.y = pOther->GetComponent<TransformComponent>()->GetPosition().y + pOther->GetHeight() / 2 + pThis->GetHeight() / 2 + 2;
				if (pos.y < 440.f)
				{
					pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
				}
			}
		}
	};

	m_pHeightCollider->SetCollisionCallBack(collisionYCallBack);

	//Add the controls
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyA, new MoveLeftCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyD, new MoveRightCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyW, new JumpCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeySpace, new ShootCommand(this, m_pBubbleSpawner));

	//Set the tag
	m_Tag = "Player";
}

PlayerCharacter::~PlayerCharacter()
{
	SafeDelete(m_pBubbleSpawner);
}

void PlayerCharacter::Update(const GameTime& gameTime)
{
	Character::Update(gameTime);
	m_pBubbleSpawner->Update(gameTime);

	if (m_Velocity.x != 0.f)
		m_Velocity.x = 0.f;

	if (GetComponent<HealthComponent>()->GetHealth() != m_PreviousHealth)
	{
		m_IsInvulnerable = true;
		m_PreviousHealth = GetComponent<HealthComponent>()->GetHealth();
	}

	if (m_IsInvulnerable)
	{
		m_InvulnerableTimer += gameTime.elapsedSec;
		if (m_InvulnerableTimer > m_TimeInvulnerable)
		{
			m_InvulnerableTimer = 0.f;
			m_IsInvulnerable = false;
		}
	}

}

void PlayerCharacter::Render(const GameTime& gameTime) const
{
	Character::Render(gameTime);
}

void PlayerCharacter::UpdateMovement(const GameTime& gameTime)
{
	Character::UpdateMovement(gameTime);
}

void PlayerCharacter::UpdateAttacking(const GameTime& gameTime)
{
	m_AttackTimer += gameTime.elapsedSec;

	if (m_AttackTimer > 2.f)
	{
		m_AttackTimer = 0.f;
		SetState(Character::State::Moving);
	}
}

bool PlayerCharacter::IsInvulnerable() const
{
	return m_IsInvulnerable;
}
