#include "TransformComponent.h"
#include "EP_Engine_PCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
	:m_Position{ 0,0,0 }
{
}

void TransformComponent::Update(const GameTime&)
{
}

void TransformComponent::Render(const GameTime&)
{
}

void TransformComponent::ChangePositionTo(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void TransformComponent::AddToPosition(float x, float y, float z)
{
	m_Position += glm::vec3(x, y, z);
}

const glm::vec3& TransformComponent::GetPosition() const
{
	return m_Position;
}
