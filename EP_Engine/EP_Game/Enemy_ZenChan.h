#pragma once
#include "Character.h"
class Enemy_ZenChan : public Character
{
public:
	Enemy_ZenChan();
	~Enemy_ZenChan();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

private:
	float m_JumpTimer;
	float m_JumpAfterS;

	bool m_FirstTimeGrounded;

	float m_BubbledTimer;
	float m_UnbubbleAfterS;

	//States
	void UpdateMovement(const GameTime& gameTime) override;
	void UpdateAttacking(const GameTime& gameTime) override;
	void UpdateBubbled(const GameTime& gameTime) override;
};

