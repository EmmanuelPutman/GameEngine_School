#include "Component.h"

class TransformComponent final : public ep::Component
{
public:
	TransformComponent();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

	void ChangePositionTo(float x, float y, float z);
	const glm::vec3& GetPosition() const;

private:
	glm::vec3 m_Position;

};

