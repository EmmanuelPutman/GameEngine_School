#pragma once
#include "Character.h"
class Enemy_ZenChan : public Character
{
public:
	Enemy_ZenChan();
	~Enemy_ZenChan();
	Enemy_ZenChan(const Enemy_ZenChan&) = delete;
	Enemy_ZenChan(Enemy_ZenChan&&) = delete;
	Enemy_ZenChan& operator= (const Enemy_ZenChan&) = delete;
	Enemy_ZenChan& operator= (const Enemy_ZenChan&&) = delete;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

private:
	float m_JumpTimer;
	float m_JumpAfterS;

	bool m_FirstTimeGrounded;

	float m_BubbledTimer;
	float m_UnbubbleAfterS;
	bool m_LookLeft;

	//States
	void UpdateMovement(const GameTime& gameTime) override;
	void UpdateAttacking(const GameTime& gameTime) override;
	void UpdateBubbled(const GameTime& gameTime) override;
};

