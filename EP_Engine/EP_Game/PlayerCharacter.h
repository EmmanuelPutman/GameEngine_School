#pragma once
#include "Character.h"
class BubbleSpawner;

class PlayerCharacter :	public Character
{
public:
    PlayerCharacter(float moveSpeed);
    ~PlayerCharacter();
    
	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

	bool IsInvulnerable() const;

private:
	BubbleSpawner* m_pBubbleSpawner;

	int m_PreviousHealth;
	bool m_IsInvulnerable;
	float m_TimeInvulnerable;
	float m_InvulnerableTimer;

	//States
	void UpdateMovement(const GameTime& gameTime) override;
	void UpdateAttacking(const GameTime& gameTime) override;
};

