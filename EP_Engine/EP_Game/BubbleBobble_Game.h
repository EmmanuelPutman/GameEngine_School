#pragma once

namespace ep {
	class Scene;
	class GameObject;
}

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
};

