#include "Component.h"

class TransformComponent final : public Component
{
public:
	TransformComponent();

	void Update() override;
	void Render() override;

	void ChangePositionTo(float x, float y, float z);
	const glm::vec3& GetPosition() const;

private:
	glm::vec3 m_Position;

};

