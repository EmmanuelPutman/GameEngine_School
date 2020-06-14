#include "EP_Engine_PCH.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent(int lives)
	:m_Lives{ lives }
	, m_StartLives{ lives }
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Update(const GameTime&)
{
}

void HealthComponent::Render(const GameTime&)
{
}

void HealthComponent::TakeDamage(int damage)
{
	m_Lives -= damage;
}

int HealthComponent::GetHealth() const
{
	return m_Lives;
}

void HealthComponent::Reset()
{	
	m_Lives = m_StartLives;
}
