#pragma once
#include "GameObject.h"

class BubbleSpawner;

class Character : public ep::GameObject
{

public:
	enum class State
	{
		Walking,
		Idle,
		Attacking,
		TakingDamage
	};

	Character(float moveSpeed);
	~Character();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

	int GetWidth() const;
	int GetHeight() const;
	float GetMoveSpeed() const;

	void SetGrounded(bool isGrounded);
	bool IsGrounded() const;
	void SetJumping(bool isJumping);
	bool IsJumping() const;
	int GetLookDirection() const;
	void SetLookDirection(int direction);

	glm::vec3 GetVelocity() const;
	void SetVelocity(const glm::vec3& newVel);
	void SetVelocity(bool xAxis, float newVel);

	void SetState(State newState);

private:
	float m_MoveSpeed;
	glm::vec3 m_Velocity;
	float m_VelYTracking;

	bool m_IsJumping;
	bool m_IsGrounded;
	
	int m_LookDirection;

	State m_State;
	float m_AttackTimer;

	BubbleSpawner* m_pBubbleSpawner;

	void UpdateMovement(const GameTime& gameTime);
};

