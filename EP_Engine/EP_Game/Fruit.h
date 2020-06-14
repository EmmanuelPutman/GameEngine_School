#pragma once
#include <GameObject.h>
class Fruit : public ep::GameObject
{
public:
	Fruit(const std::string& fileName, const glm::vec3& pos, int score);
	~Fruit();
	Fruit(const Fruit&) = delete;
	Fruit(Fruit&&) = delete;
	Fruit& operator= (const Fruit&) = delete;
	Fruit& operator= (const Fruit&&) = delete;

	void Update(const GameTime& gameTime);
	void Render(const GameTime& gameTime) const;

	bool IsCollected() const;
	void Collect();

	int GetScore() const;

private:
	int m_Score;
	bool m_IsCollected;
	float m_yMoveSpeed;
};

