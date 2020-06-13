#pragma once

namespace ep{
	class GameObject;
}

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Update();

private:
	std::vector<ep::GameObject*> m_pEnemies;
};

