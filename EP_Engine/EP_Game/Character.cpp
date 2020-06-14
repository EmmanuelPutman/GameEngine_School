#include "EP_Engine_PCH.h"
#include "Character.h"

#include "Logger.h"

#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"

Character::Character(float moveSpeed, int lives, int damage, const std::string& startAnimName, int animCols, int animRows, float animSwapsAfterS)
	:m_MoveSpeed{ moveSpeed }
	, m_Damage{ damage }
	, m_Velocity{}
	, m_VelYTracking{ 0.f }
	, m_IsGrounded{ false }
	, m_AttackTimer{ 0.f }
	, m_State{ State::Moving }
	, m_LookDirection{ -1 }
	, m_IsJumping{ false }
{
	//Transform
	TransformComponent* pTransform = new TransformComponent();
	this->AddComponent(pTransform);

	//Animation
	AnimationComponent* pAnim = new AnimationComponent(startAnimName, animCols, animRows, animSwapsAfterS);
	this->AddComponent(pAnim);
	
	//Add HealthComponent
	HealthComponent* pHealth = new HealthComponent(lives);
	this->AddComponent(pHealth);

	//Collision for right and left
	m_pWidthCollider = new ColliderComponent(pAnim->GetFrameWidth(), pAnim->GetFrameHeight()-6);
	this->AddComponent(m_pWidthCollider);


	//Collision for top and bottom
	m_pHeightCollider = new ColliderComponent(pAnim->GetFrameWidth() - 4, pAnim->GetFrameHeight());
	this->AddComponent(m_pHeightCollider);
	
	//Trigger to check if grounded
	ColliderComponent* pGroundedTrigger = new ColliderComponent(pAnim->GetFrameWidth() - 6, pAnim->GetFrameHeight() + 8, true);
	this->AddComponent(pGroundedTrigger);

	auto groundedCallBack = [](GameObject* pThis, GameObject*)
	{
		//Logger::GetInstance().Log("ENTERED a trigger");
		static_cast<Character*>(pThis)->SetGrounded(true);
	};

	pGroundedTrigger->SetTriggerCallBack(groundedCallBack);

	auto notgroundedCallBack = [](GameObject* pThis, GameObject* )
	{
		//Logger::GetInstance().Log("Exited a trigger");
		static_cast<Character*>(pThis)->SetGrounded(false);
	};

	pGroundedTrigger->SetTriggerExitCallBack(notgroundedCallBack);

}

Character::~Character()
{
}

void Character::Update(const GameTime& gameTime)
{
	ep::GameObject::Update(gameTime);

	switch (m_State)
	{
	case State::Moving:
		UpdateMovement(gameTime);
		break;

	case State::Attacking:
		UpdateAttacking(gameTime);
		break;

	case State::Idle:
		UpdateIdle(gameTime);
		break;

	case State::TakingDamage:
		UpdateTakingDamage(gameTime);
		break;

	case State::Bubbled:
		UpdateBubbled(gameTime);
		break;
	}

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

int Character::GetDamage() const
{
	return m_Damage;
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
	this->GetComponent<AnimationComponent>()->SetDirection(direction);
}

Character::State Character::GetState() const
{
	return m_State;
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

	for (const auto state : m_StateSettings)
	{
		if (state.state == newState)
		{ 
			m_State = state.state;
			this->GetComponent<AnimationComponent>()->SetTexture(state.animName, state.columns, state.rows, state.swapFrameAfterS);
			return;
		}
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

void Character::UpdateAttacking(const GameTime&)
{
}

void Character::UpdateIdle(const GameTime&)
{
}

void Character::UpdateTakingDamage(const GameTime&)
{
}

void Character::UpdateBubbled(const GameTime&)
{
}
