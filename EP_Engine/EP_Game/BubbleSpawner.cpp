#include "EP_Engine_PCH.h"
#include "BubbleSpawner.h"

#include "Bubble.h"

#include "SceneManager.h"
#include "Scene.h"

#include "CollisionManager.h"
#include "ColliderComponent.h"

BubbleSpawner::BubbleSpawner()
	:m_Timer{ 0.f }
	, m_TimeFloating{ 3.f }
{
}

BubbleSpawner::~BubbleSpawner()
{
}

void BubbleSpawner::ShootBubble(int direction, const glm::vec3 pos)
{
	if (m_pBubble == nullptr)
	{
		SafeDelete(m_pBubble);
		m_pBubble = new Bubble(pos, 45.f, direction);
		ep::SceneManager::GetInstance().GetScene()->Add(m_pBubble);
	}
}

void BubbleSpawner::Update(const GameTime& gameTime)
{
	if (m_pBubble != nullptr)
	{
		m_Timer += gameTime.elapsedSec;

		if (m_Timer > m_TimeFloating || static_cast<Bubble*>(m_pBubble)->GetShouldBeRemoved())
		{
			m_Timer = 0.f;
			ep::CollisionManager::GetInstance().RemoveCollision(m_pBubble->GetComponent<ColliderComponent>());
			ep::SceneManager::GetInstance().GetScene()->Remove(m_pBubble);
			m_pBubble = nullptr;
		}

	}
}
