#include "EP_Engine_PCH.h"
#include "Character.h"

#include "BubbleSpawner.h"

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
	, m_AttackTimer{ 0.f }
	, m_State{ State::Walking }
	, m_LookDirection{ -1 }
{
	m_pBubbleSpawner = new BubbleSpawner();


	//Transform
	TransformComponent* pTransform = new TransformComponent();
	this->AddComponent(pTransform);

	//Animation
	AnimationComponent* pAnim = new AnimationComponent("CharacterRun.png", 7, 1, 0.09f);
	this->AddComponent(pAnim);
	
	//Collision for right and left
	ColliderComponent* pWidthCollider = new ColliderComponent(pAnim->GetFrameWidth(), pAnim->GetFrameHeight()-6);
	this->AddComponent(pWidthCollider);

	auto collisionXCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (static_cast<Character*>(pThis)->IsJumping())
			return;

		if (pOther != pThis && pOther != nullptr && pOther->GetTag() == "Block")
		{
			if (static_cast<Character*>(pThis)->GetVelocity().x > 0.f)
			{
				//Logger::GetInstance().Log("Right side was hit");
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x - pOther->GetWidth()/2 - pThis->GetWidth()/2 - 4;
				if(pos.x > 46.f)
				{ 
					pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
				}
			}
			else if (static_cast<Character*>(pThis)->GetVelocity().x < 0.f)
			{
				//Logger::GetInstance().Log("Left side was hit");
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.x = pOther->GetComponent<TransformComponent>()->GetPosition().x + pOther->GetWidth() / 2 + pThis->GetWidth() / 2 +4;
				if(pos.x < 600.f)
				{ 
					pThis->GetComponent<TransformComponent>()->ChangePositionTo(pos.x, pos.y, pos.z);
				}
			}
		}
	};

	pWidthCollider->SetCollisionCallBack(collisionXCallBack);

	//Collision for top and bottom
	ColliderComponent* pHeightCollider = new ColliderComponent(pAnim->GetFrameWidth() - 6, pAnim->GetFrameHeight());
	this->AddComponent(pHeightCollider);

	auto collisionYCallBack = [](GameObject* pThis, GameObject* pOther)
	{
		if (static_cast<Character*>(pThis)->IsJumping())
			return;
		if (pOther != pThis && pOther != nullptr && pOther->GetTag() == "Block")
		{
			if (static_cast<Character*>(pThis)->GetVelocity().y > 0.f)
			{
				glm::vec3 pos = pThis->GetComponent<TransformComponent>()->GetPosition();
				pos.y = pOther->GetComponent<TransformComponent>()->GetPosition().y - pOther->GetHeight() / 2 - pThis->GetHeight()/2 -2;
				if(pos.y > 40.f)
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

	pHeightCollider->SetCollisionCallBack(collisionYCallBack);
	
	//Trigger to check if grounded
	ColliderComponent* pGroundedTrigger = new ColliderComponent(pAnim->GetFrameWidth() - 6, pAnim->GetFrameHeight() + 8, true);
	this->AddComponent(pGroundedTrigger);

	auto groundedCallBack = [](GameObject* pThis, GameObject*)
	{
		//Logger::GetInstance().Log("ENTERED a trigger");
		static_cast<Character*>(pThis)->SetGrounded(true);
	};

	pGroundedTrigger->SetTriggerCallBack(groundedCallBack);

	auto notgroundedCallBack = [](GameObject* pThis, GameObject*)
	{
		//Logger::GetInstance().Log("Exited a trigger");
		static_cast<Character*>(pThis)->SetGrounded(false);
	};

	pGroundedTrigger->SetTriggerExitCallBack(notgroundedCallBack);


	//Add the controls
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyA, new MoveLeftCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyD, new MoveRightCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyW, new JumpCommand(this));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeySpace, new ShootCommand(this, m_pBubbleSpawner));
}

Character::~Character()
{
	SafeDelete(m_pBubbleSpawner);
}

void Character::Update(const GameTime& gameTime)
{
	ep::GameObject::Update(gameTime);
	m_pBubbleSpawner->Update(gameTime);

#pragma region States

	switch(m_State)
	{
	case State::Attacking:
		m_AttackTimer += gameTime.elapsedSec;

		if (m_AttackTimer > 2.f)
			SetState(Character::State::Walking);
		break;
	case State::Walking:
		UpdateMovement(gameTime);
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

bool Character::IsGrounded() const
{
	return m_IsGrounded;
}

void Character::SetJumping(bool isJumping)
{
	m_IsJumping = isJumping;
}

bool Character::IsJumping() const
{
	return m_IsJumping;
}

int Character::GetLookDirection() const
{
	return m_LookDirection;
}

void Character::SetLookDirection(int direction)
{
	m_LookDirection = direction;
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

void Character::SetState(State newState)
{
	m_AttackTimer = 0.f;
	switch (newState)
	{
	case State::Attacking:
		m_State = State::Attacking;
		this->GetComponent<AnimationComponent>()->SetTexture("CharacterAttack.png", 8, 1, 0.25f);
		break;

	case State::Walking:
		m_State = State::Walking;
		this->GetComponent<AnimationComponent>()->SetTexture("CharacterRun.png", 7, 1, 0.09f);
		break;
	}
}

void Character::UpdateMovement(const GameTime& gameTime)
{
	glm::vec3 posAdd{};
	posAdd.x = m_Velocity.x * m_MoveSpeed * gameTime.elapsedSec;
	posAdd.y = m_Velocity.y * m_MoveSpeed * gameTime.elapsedSec;
	if (m_IsJumping)
	{
		posAdd.y = m_Velocity.y * m_MoveSpeed * 1.75f * gameTime.elapsedSec;
	}

	if (m_Velocity.y < 0.f)
		m_VelYTracking -= posAdd.y;

	GetComponent<TransformComponent>()->AddToPosition(posAdd.x, posAdd.y, posAdd.z);

	if (m_Velocity.x != 0.f)
		m_Velocity.x = 0.f;

	if (m_VelYTracking > 90.f && m_Velocity.y < 0.f)
	{
		m_IsJumping = false;
		m_Velocity.y = 1.f;
		m_VelYTracking = 0.f;
	}

	if (!m_IsGrounded)
	{
		if (m_IsJumping == false)
		{
			m_Velocity.y = 1.f;
		}
	}
}
