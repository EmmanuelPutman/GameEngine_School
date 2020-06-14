#pragma once
#include "GameObject.h"

class ColliderComponent;

class Character : public ep::GameObject
{

public:
	enum class State
	{
		Idle,
		Moving,
		Attacking,
		TakingDamage,
		Bubbled,
	};

	struct StateSettings
	{
		std::string animName;
		State state;
		int columns;
		int rows;
		float swapFrameAfterS;
	};

	Character(float moveSpeed, int lives, int damage, const std::string& startAnimName, int animCols, int animRows, float animSwapsAfterS);
	~Character();
	Character(const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator= (const Character&) = delete;
	Character& operator= (const Character&&) = delete;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

	int GetWidth() const;
	int GetHeight() const;
	float GetMoveSpeed() const;
	int GetDamage() const;

	void SetGrounded(bool isGrounded);
	bool IsGrounded() const;
	void SetJumping(bool isJumping);
	bool IsJumping() const;
	int GetLookDirection() const;
	void SetLookDirection(int direction);

	State GetState() const;

	glm::vec3 GetVelocity() const;
	void SetVelocity(const glm::vec3& newVel);
	void SetVelocity(bool xAxis, float newVel);

	void SetState(State newState);

protected:
	std::string m_StartAnim;

	float m_MoveSpeed;
	int m_Damage;

	glm::vec3 m_Velocity;
	float m_VelYTracking;

	bool m_IsJumping;
	bool m_IsGrounded;
	
	int m_LookDirection;

	State m_State;
	float m_AttackTimer;
	
	std::vector< StateSettings > m_StateSettings;

	ColliderComponent* m_pHeightCollider;
	ColliderComponent* m_pWidthCollider;

	//States updates
	virtual void UpdateMovement(const GameTime& gameTime);
	virtual void UpdateAttacking(const GameTime& gameTime);
	virtual void UpdateIdle(const GameTime& gameTime);
	virtual void UpdateTakingDamage(const GameTime& gameTime);
	virtual void UpdateBubbled(const GameTime& gameTime);
};

