#include "EP_Engine_PCH.h"
#include "FruitManager.h"

#include <algorithm>

#include "SceneManager.h"
#include "Scene.h"	
#include "CollisionManager.h"

#include "ColliderComponent.h"
#include "Fruit.h"


FruitManager::FruitManager()
{
}

FruitManager::~FruitManager()
{
}

void FruitManager::Update()
{
	std::vector<ep::GameObject*> remove{};
	for (ep::GameObject* pFruit : m_pFruits)
	{
		if (pFruit != nullptr && static_cast<Fruit*>(pFruit)->IsCollected())
		{
			remove.push_back(pFruit);
		}
	}

	for (ep::GameObject* pFruit : remove)
	{
		m_Score += static_cast<Fruit*>(pFruit)->GetScore();

		for (ColliderComponent* pCollision : pFruit->GetComponents<ColliderComponent>())
		{
			pCollision->FlagForDelete();
			ep::CollisionManager::GetInstance().RemoveCollision(pCollision);
		}
		ep::SceneManager::GetInstance().GetScene()->Remove(pFruit);

		auto it = std::remove(m_pFruits.begin(), m_pFruits.end(), pFruit);

		pFruit = nullptr;
		m_pFruits.erase(it);

	}
}

void FruitManager::AddFruit(ep::GameObject* fruit)
{
	ep::SceneManager::GetInstance().GetScene()->Add(fruit);
	m_pFruits.push_back(fruit);
}

int FruitManager::GetScore() const
{
	return m_Score;
}
