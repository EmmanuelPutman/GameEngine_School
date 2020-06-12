#include "EP_Engine_PCH.h"
#include "Bubble.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"

Bubble::Bubble(const glm::vec3& pos, float moveSpeed, int direction)
	:m_MoveSpeed{ moveSpeed }
	, m_Direction{ direction }
{
	TransformComponent* pTransform = new TransformComponent();
	pTransform->ChangePositionTo(pos.x, pos.y, pos.z);
	this->AddComponent(pTransform);

	SpriteComponent* pSprite = new SpriteComponent("Bubble.png");
	this->AddComponent(pSprite);

}

Bubble::~Bubble()
{
}

void Bubble::Update(const GameTime& gameTime)
{
	ep::GameObject::Update(gameTime);
	glm::vec3 addPos{};
	addPos.x = m_Direction * m_MoveSpeed * gameTime.elapsedSec;
	addPos.x = m_Direction * m_MoveSpeed * gameTime.elapsedSec;

	this->GetComponent<TransformComponent>()->AddToPosition(addPos.x, addPos.y, addPos.z);
}

void Bubble::Render(const GameTime& gameTime) const
{
	ep::GameObject::Render(gameTime);
}
