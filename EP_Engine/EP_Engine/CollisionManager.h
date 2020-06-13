#pragma once
#include "Singleton.h"
class ColliderComponent;

namespace ep
{
	class CollisionManager : public ep::Singleton<CollisionManager>
	{
	public:
		CollisionManager();
		~CollisionManager() = default;

		void AddCollision(ColliderComponent* pCollision);
		void RemoveCollision(ColliderComponent* pCollision);

		void Update();

	private:
		std::vector<ColliderComponent*> m_pCollisions;

		std::vector<ColliderComponent*> m_pCollisionsToRemove;
	};
}

