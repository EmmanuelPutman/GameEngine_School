#pragma once
class Bubble;

class BubbleSpawner
{
public:
	BubbleSpawner();
	~BubbleSpawner();
	BubbleSpawner(const BubbleSpawner&) = delete;
	BubbleSpawner(BubbleSpawner&&) = delete;
	BubbleSpawner& operator= (const BubbleSpawner&) = delete;
	BubbleSpawner& operator= (const BubbleSpawner&&) = delete;

	void ShootBubble(int direction, const glm::vec3 pos);
	void Update(const GameTime& gameTime);

private:
	Bubble* m_pBubble;
	float m_Timer;
	float m_TimeFloating;
};

