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

		void Update();

	private:
		std::vector<ColliderComponent*> m_pCollisions;
	};
}

