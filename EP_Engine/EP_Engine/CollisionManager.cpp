#include "EP_Engine_PCH.h"
#include "CollisionManager.h"

#include "Logger.h"
#include "ColliderComponent.h"

#include <algorithm>

ep::CollisionManager::CollisionManager()
{
}

void ep::CollisionManager::AddCollision(ColliderComponent* pCollision)
{
	for (ColliderComponent* pCollider : m_pCollisions)
	{
		if (pCollider == pCollision)
		{
			ep::Logger::GetInstance().Error("{__CollisionManager::AddCollision__} CollisionComponent already added.");
			return;
		}
	}

	m_pCollisions.push_back(pCollision);
}

void ep::CollisionManager::RemoveCollision(ColliderComponent* pCollision)
{
	m_pCollisionsToRemove.push_back(pCollision);
}

void ep::CollisionManager::Update()
{
	for (ColliderComponent* pCollision : m_pCollisions)
	{
		for (ColliderComponent* pCompareCollision : m_pCollisions)
		{
			if (pCollision != pCompareCollision)
			{
				pCollision->CheckCollision(pCompareCollision);
			}
		}
	}

	for (ColliderComponent* pCollision : m_pCollisions)
	{
		for (ColliderComponent* pCompareCollision : m_pCollisions)
		{
			if (pCompareCollision->IsFlaggedForDelete())
			{
				if (pCollision != pCompareCollision)
				{
					pCollision->Exit();
				}
			}
		}
	}

	for (ColliderComponent* pCollider : m_pCollisionsToRemove)
	{
		auto it = std::remove(m_pCollisions.begin(), m_pCollisions.end(), pCollider);
		m_pCollisions.erase(it);
	}

	m_pCollisionsToRemove.clear();
}
