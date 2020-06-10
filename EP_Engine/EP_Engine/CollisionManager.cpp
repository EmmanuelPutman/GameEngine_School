#include "EP_Engine_PCH.h"
#include "CollisionManager.h"

#include "Logger.h"
#include "ColliderComponent.h"

ep::CollisionManager::CollisionManager()
{
}

void ep::CollisionManager::AddCollision(ColliderComponent* pCollision)
{
	for(ColliderComponent* pCollider : m_pCollisions)
	{ 
		if (pCollider == pCollision)
		{
			ep::Logger::GetInstance().Error("{__CollisionManager::AddCollision__} CollisionComponent already added.");
			return;
		}
	}

	m_pCollisions.push_back(pCollision);
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
}
