#pragma once

namespace ep{
	class GameObject;
}

class FruitManager;

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	EnemyManager(const EnemyManager&) = delete;
	EnemyManager(EnemyManager&&) = delete;
	EnemyManager& operator= (const EnemyManager&) = delete;
	EnemyManager& operator= (const EnemyManager&&) = delete;

	void Update();

	int GetEnemiesAlive() const;
	int GetScore() const;

private:
	std::vector<ep::GameObject*> m_pEnemies;

	FruitManager* m_pFruitManager;

	int m_StartNrOfEnemies;
	int m_NrOfEnemiesAlive;
	int m_Score;
};

