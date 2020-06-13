#include "EP_Engine_PCH.h"
#include "Bubble.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

#include "Character.h"
#include "SceneManager.h"
#include "Scene.h"

Bubble::Bubble(const glm::vec3& pos, float moveSpeed, int direction)
	:m_MoveSpeed{ moveSpeed }
	, m_Direction{ direction }
{
	TransformComponent* pTransform = new TransformComponent();
	pTransform->ChangePositionTo(pos.x, pos.y, pos.z);
	this->AddComponent(pTransform);

	SpriteComponent* pSprite = new SpriteComponent("Bubble.png");
	this->AddComponent(pSprite);

	ColliderComponent* pBubbleTrigger = new ColliderComponent(pSprite->GetWidth(), pSprite->GetHeight(), true);
	this->AddComponent(pBubbleTrigger);

	auto enemyHitCallBack = [pBubbleTrigger](ep::GameObject* pThis, ep::GameObject* pOther)
	{
		if (pOther != pThis && pOther != nullptr && pOther->GetTag() == "Enemy")
		{
			static_cast<Character*>(pOther)->SetState(Character::State::Bubbled);
			pOther->GetComponent<TransformComponent>()->AddToPosition(0.f, -5.f, 0.f);
			pBubbleTrigger->FlagForDelete();
			static_cast<Bubble*>(pThis)->SetShouldBeRemoved(true);
		}
	};

	pBubbleTrigger->SetTriggerCallBack(enemyHitCallBack);


	//Set tag
	m_Tag = "Bubble";
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

bool Bubble::GetShouldBeRemoved()
{
	return m_ToBeRemoved;
}

void Bubble::SetShouldBeRemoved(bool remove)
{
	m_ToBeRemoved = remove;
}
