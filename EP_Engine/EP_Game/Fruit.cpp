#include "EP_Engine_PCH.h"
#include "Fruit.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

#include "Logger.h"

Fruit::Fruit(const std::string& fileName, const glm::vec3& pos, int score)
	:m_Score{ score }
	, m_IsCollected{ false }
	, m_yMoveSpeed{ 7.5f }
{
	TransformComponent* pTransform = new TransformComponent();
	pTransform->ChangePositionTo(pos.x, pos.y - 50.f, pos.z);
	this->AddComponent(pTransform);

	SpriteComponent* pSprite = new SpriteComponent(fileName);
	this->AddComponent(pSprite);

	ColliderComponent* pTrigger = new ColliderComponent(pSprite->GetWidth(), pSprite->GetHeight(), true);
	this->AddComponent(pTrigger);

	auto pickUpCallBack = [pTrigger](ep::GameObject* pThis, ep::GameObject* pOther)
	{

		if (pOther != pThis && pOther != nullptr && pOther->GetTag() == "Player")
		{
			if(static_cast<Fruit*>(pThis)->IsCollected() == false)
			{ 
				ep::Logger::GetInstance().Log("Collected Fruit, score + " + std::to_string(static_cast<Fruit*>(pThis)->GetScore()));
				static_cast<Fruit*>(pThis)->Collect();
			}
		}
	};

	pTrigger->SetTriggerCallBack(pickUpCallBack);

	m_Tag = "Fruit";
}

Fruit::~Fruit()
{
}

void Fruit::Update(const GameTime& gameTime)
{
	ep::GameObject::Update(gameTime);
	this->GetComponent<TransformComponent>()->AddToPosition(0.f, m_yMoveSpeed * gameTime.elapsedSec, 0.f);
}

void Fruit::Render(const GameTime& gameTime) const
{
	ep::GameObject::Render(gameTime);
}

bool Fruit::IsCollected() const
{
	return m_IsCollected;
}

void Fruit::Collect()
{
	m_IsCollected = true;
}

int Fruit::GetScore() const
{
	return m_Score;
}
