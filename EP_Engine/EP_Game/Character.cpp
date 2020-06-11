#include "EP_Engine_PCH.h"
#include "Character.h"

#include "InputManager.h"
#include "GameCommands.h"

//#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"

Character::Character(float moveSpeed)
	:m_MoveSpeed{ moveSpeed }
	, m_Velocity{}
	, m_VelYTracking{ 0.f }
	, m_IsGrounded{ false }
{
	TransformComponent* pTransform = new TransformComponent();
	this->AddComponent(pTransform);

	AnimationComponent* pAnim = new AnimationComponent("CharacterRun.png", 7, 1, 0.09f);
	this->AddComponent(pAnim);

	ColliderComponent* pWidthCollider = new ColliderComponent(pAnim->GetFrameWidth(), pAnim->GetFrameHeight() - 5);
	this->AddComponent(pWidthCollider);

	auto collisionXCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (pOther != nullptr && pOther->GetTag() == "Block")
		{
			if (static_cast<Character*>(pThis)->GetVelocity().x > 0.f)
			{
				Logger::GetInstance().Log("Right side was hit");
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x - pOther->GetWidth()/2 - pThis->GetWidth()/2 - 2;
				pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
			}
			else if (static_cast<Character*>(pThis)->GetVelocity().x < 0.f)
			{
				Logger::GetInstance().Log("Left side was hit");
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x + pOther->GetWidth() / 2 + pThis->GetWidth() / 2 +2;
				pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
			}
		}
	};

	pWidthCollider->SetCollisionCallBack(collisionXCallBack);

	ColliderComponent* pHeightCollider = new ColliderComponent(pAnim->GetFrameWidth() - 5, pAnim->GetFrameHeight());
	this->AddComponent(pHeightCollider);

	auto collisionYCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (pOther != nullptr && pOther->GetTag() == "Block")
		{
			if (static_cast<Character*>(pThis)->GetVelocity().y > 0.f)
			{
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.y = pOther->GetComponent<TransformComponent>()->GetPosition().y - pOther->GetHeight() / 2 - pThis->GetHeight()/2 -1;
				pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
				static_cast<Character*>(pThis)->SetVelocity(false, 0.f);
			}
			else if (static_cast<Character*>(pThis)->GetVelocity().y < 0.f)
			{
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.y = pOther->GetComponent<TransformComponent>()->GetPosition().y + pOther->GetHeight() / 2 + pThis->GetHeight() / 2 + 2;
				pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
			}
		}
	};

	pHeightCollider->SetCollisionCallBack(collisionYCallBack);


	ColliderComponent* pGroundedTrigger = new ColliderComponent(pAnim->GetFrameWidth() - 6, pAnim->GetFrameHeight() +8, true);
	this->AddComponent(pGroundedTrigger);

	auto groundedCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (pOther != nullptr)
		{
			if (static_cast<Character*>(pThis)->GetVelocity().y > 0.f)
			{
				static_cast<Character*>(pThis)->SetGrounded(true);
			}
		}
	};

	pGroundedTrigger->SetTriggerCallBack(groundedCallBack);

	//Add the controls
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyA, new MoveLeftCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyD, new MoveRightCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeySpace, new JumpCommand(this));
}

Character::~Character()
{
}

void Character::Update(const GameTime& gameTime)
{
	ep::GameObject::Update(gameTime);

#pragma region Movement

	glm::vec3 posAdd{};
	posAdd.x = m_Velocity.x * m_MoveSpeed * gameTime.elapsedSec;
	posAdd.y = m_Velocity.y * m_MoveSpeed*2 * gameTime.elapsedSec;
	if(m_Velocity.y < 0.f)
		m_VelYTracking -= posAdd.y;

	GetComponent<TransformComponent>()->AddToPosition(posAdd.x, posAdd.y, posAdd.z);

	if(m_Velocity.x != 0.f)
		m_Velocity.x = 0.f;

	if (m_VelYTracking > 90.f && m_Velocity.y < 0.f)
	{
		m_Velocity.y = 1.f;
		m_VelYTracking = 0.f;
	}

	if (m_IsGrounded)
	{ 

	}
	else
	{
		Logger::GetInstance().Log("FALLING DOWNN");
		m_Velocity.y = 1.f;
	}

#pragma endregion
}

void Character::Render(const GameTime& gameTime) const
{
	ep::GameObject::Render(gameTime);
}

int Character::GetWidth() const
{
	return m_Width;
}

int Character::GetHeight() const
{
	return m_Height;
}

float Character::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

void Character::SetGrounded(bool isGrounded)
{
	m_IsGrounded = isGrounded;
}

glm::vec3 Character::GetVelocity() const
{
	return m_Velocity;
}

void Character::SetVelocity(const glm::vec3& newVel)
{
	m_Velocity = newVel;
}

void Character::SetVelocity(bool xAxis, float newVel)
{
	if (xAxis)
	{
		m_Velocity.x = newVel;
		return;
	}

	m_Velocity.y = newVel;
}
