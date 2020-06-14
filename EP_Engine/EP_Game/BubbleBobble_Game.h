#pragma once

namespace ep {
	class Scene;
	class GameObject;
}

class LevelParser_Pyxel;
class EnemyManager;

class BubbleBobble_Game
{
public:
	BubbleBobble_Game(const GameTime& gameTime);
	~BubbleBobble_Game();
	BubbleBobble_Game(const BubbleBobble_Game&) = delete;
	BubbleBobble_Game(BubbleBobble_Game&&) = delete;
	BubbleBobble_Game& operator= (const BubbleBobble_Game&) = delete;
	BubbleBobble_Game& operator= (const BubbleBobble_Game&&) = delete;

	void Update(const GameTime& gameTime);

private:
	void Initialize(const GameTime& gameTime);

	ep::Scene* m_pScene;
	ep::GameObject* character;

	LevelParser_Pyxel* m_pParser;
	EnemyManager* m_pEnemySpawner;

	int m_LevelNr;
	float m_NextLevelTimer;
	float m_NextLevelAfterS;
	bool m_GameOver;

	int m_Score;
	int m_PlayerLives;
	int m_PrevLevelScore;
	ep::GameObject* m_pPlayerLivesObj;
	ep::GameObject* m_pScoreObj;
	
	void CreateLevel(const GameTime& gameTime);

	void GoToNextLevel(const GameTime& gameTime);
};

