#include "EP_Engine_PCH.h"
#include "Enemy_ZenChan.h"

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"

#include "PlayerCharacter.h"

#include "Logger.h"
#include "Bubble.h"

Enemy_ZenChan::Enemy_ZenChan()
	:Character(20.f, 1, 1, "ZenChanWalking.png", 4, 1, 0.3f)
	, m_JumpTimer{ 0.f }
	, m_JumpAfterS{ 9.f }
	, m_FirstTimeGrounded{ true }
	, m_BubbledTimer{ 0.f }
	, m_UnbubbleAfterS{ 5.f }
{
	//Set the different states
	StateSettings walking{ "ZenChanWalking.png", State::Moving, 4, 1, 0.3f };
	StateSettings bubbled{ "ZenChanBubbled.png", State::Bubbled, 3, 1, 0.5f };
	m_StateSettings.push_back(walking);
	m_StateSettings.push_back(bubbled);

	//Set the collision callback for the left and right
	auto collisionWidthCallBack = [](ep::GameObject*, ep::GameObject*)
	{
	};
	m_pWidthCollider->SetCollisionCallBack(collisionWidthCallBack);

	//Set a trigger to go opposite way when triggered
	ColliderComponent* pRotateTrigger = new ColliderComponent(this->GetComponent<AnimationComponent>()->GetFrameWidth(), this->GetComponent<AnimationComponent>()->GetFrameHeight() - 6, true);
	this->AddComponent(pRotateTrigger);

	auto rotateCallBack = [](ep::GameObject* pThis, ep::GameObject* pOther)
	{
		ep::Logger::GetInstance().Log("COLLIDING");
		if (static_cast<Character*>(pThis)->IsJumping() || pOther->GetTag() == "Bubble")
		{ 
			return;
		}

		if (pThis != pOther && pOther != nullptr)
		{
			Character* pCharacter = static_cast<Character*>(pThis);

			if (pOther->GetTag() == "Player" && pCharacter->GetState() == State::Bubbled)
			{
				

				return;
			}

			if (pOther->GetTag() == "Player")
			{
				if (pOther->GetComponent<HealthComponent>()->GetHealth() > 0 && static_cast<PlayerCharacter*>(pOther)->IsInvulnerable() == false)
				{
					ep::Logger::GetInstance().Log("Damaged");
					pOther->GetComponent<HealthComponent>()->TakeDamage(pCharacter->GetDamage());
				}
			}
			if (pOther->GetTag() == "Block")
			{
				float newVel = -pCharacter->GetVelocity().x;
				pCharacter->SetVelocity(true, newVel);
				pCharacter->SetLookDirection(newVel < 0.f ? -1 : 1);
			}

		}
	};
	pRotateTrigger->SetTriggerCallBack(rotateCallBack);

	//Set the collision callback for the top and bottom
	auto collisionHeightCallBack = [](ep::GameObject* pThis, ep::GameObject* pOther)
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
	m_pHeightCollider->SetCollisionCallBack(collisionHeightCallBack);

	//Set the tag
	m_Tag = "Enemy";
}

Enemy_ZenChan::~Enemy_ZenChan()
{
}

void Enemy_ZenChan::Update(const GameTime& gameTime)
{
	Character::Update(gameTime);
}

void Enemy_ZenChan::Render(const GameTime& gameTime) const
{
	Character::Render(gameTime);
}

void Enemy_ZenChan::UpdateMovement(const GameTime& gameTime)
{
	Character::UpdateMovement(gameTime);

	if (m_FirstTimeGrounded == true && m_IsGrounded && m_IsJumping == false)
	{
		m_FirstTimeGrounded = false;
		m_Velocity.x = (float)m_LookDirection;
	}

	if (m_IsGrounded)
	{
		m_JumpTimer += gameTime.elapsedSec;

		if (m_JumpTimer > m_JumpAfterS)
		{
			m_Velocity.x = 0.f;
			m_IsJumping = true;
			m_FirstTimeGrounded = true;
			m_Velocity.y = -1.f;
			m_JumpTimer = 0.f;
		}
	}
}

void Enemy_ZenChan::UpdateAttacking(const GameTime&)
{
}

void Enemy_ZenChan::UpdateBubbled(const GameTime& gameTime)
{
	m_BubbledTimer += gameTime.elapsedSec;

	if (m_BubbledTimer > m_UnbubbleAfterS)
	{
		m_BubbledTimer = 0.f;
		SetState(Character::State::Moving);
		m_FirstTimeGrounded = true;
	}
}
