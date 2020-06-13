#include "EP_Engine_PCH.h"
#include "EnemyManager.h"

#include <algorithm>

#include "Enemy_ZenChan.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "Scene.h"	
#include "CollisionManager.h"

#include "ColliderComponent.h"

EnemyManager::EnemyManager()
{
	ep::GameObject* pEnemy = new Enemy_ZenChan();
	pEnemy->GetComponent<TransformComponent>()->ChangePositionTo(100.f, 150.f, 0.f);
	ep::SceneManager::GetInstance().GetScene()->Add(pEnemy);
	m_pEnemies.push_back(pEnemy);

	ep::GameObject* pEnemy1 = new Enemy_ZenChan();
	pEnemy1->GetComponent<TransformComponent>()->ChangePositionTo(275.f, 150.f, 0.f);
	ep::SceneManager::GetInstance().GetScene()->Add(pEnemy1);
	m_pEnemies.push_back(pEnemy1);

	ep::GameObject* pEnemy2 = new Enemy_ZenChan();
	pEnemy2->GetComponent<TransformComponent>()->ChangePositionTo(500.f, 150.f, 0.f);
	ep::SceneManager::GetInstance().GetScene()->Add(pEnemy2);
	m_pEnemies.push_back(pEnemy2);
}

EnemyManager::~EnemyManager()
{
	//for (ep::GameObject* pEnemy : m_pEnemies)
	//	SafeDelete(pEnemy);
}

void EnemyManager::Update()
{
	std::vector<ep::GameObject*> remove{};
	for (ep::GameObject* pEnemy : m_pEnemies)
	{
		if (pEnemy != nullptr && pEnemy->GetComponent<HealthComponent>()->GetHealth() <= 0)
		{
			remove.push_back(pEnemy);
		}
	}

	/*
	for (size_t i = 0; i < remove.size(); ++i)
	{
		for (ColliderComponent* pCollision : m_pEnemies[i]->GetComponents<ColliderComponent>())
		{
			pCollision->FlagForDelete();
			ep::CollisionManager::GetInstance().RemoveCollision(pCollision);
		}
		ep::SceneManager::GetInstance().GetScene()->Remove(m_pEnemies[i]);

		auto it = std::remove(m_pEnemies.begin(), m_pEnemies.end(), m_pEnemies[i]);

		m_pEnemies[i] = nullptr;
		m_pEnemies.erase(it);
	}
	*/

	for (ep::GameObject* pEnemy : remove)
	{
		for (ColliderComponent* pCollision : pEnemy->GetComponents<ColliderComponent>())
		{
			pCollision->FlagForDelete();
			ep::CollisionManager::GetInstance().RemoveCollision(pCollision);
		}
		ep::SceneManager::GetInstance().GetScene()->Remove(pEnemy);

		auto it = std::remove(m_pEnemies.begin(), m_pEnemies.end(), pEnemy);

		pEnemy = nullptr;
		m_pEnemies.erase(it);
	}
}


