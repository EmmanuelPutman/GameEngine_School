#pragma once
#include "Component.h"
class HealthComponent :	public ep::Component
{
public:
	HealthComponent(int lives);
	~HealthComponent();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

	void TakeDamage(int damage);
	int GetHealth() const;

private:
	int m_Lives;
	int m_StartLives;
};

