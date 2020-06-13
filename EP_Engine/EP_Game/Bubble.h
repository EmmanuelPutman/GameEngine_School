#pragma once
#include "GameObject.h"
class Bubble : public ep::GameObject
{
public:
	Bubble(const glm::vec3& pos, float moveSpeed, int m_Direction);
	~Bubble();
	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) const override;

	bool GetShouldBeRemoved();
	void SetShouldBeRemoved(bool remove);

private:
	float m_MoveSpeed;
	int m_Direction;
	bool m_ToBeRemoved;
};

