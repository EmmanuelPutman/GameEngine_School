#include "EP_Engine_PCH.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"

#include "Renderer.h"
#include "Logger.h"
#include "CollisionManager.h"

#include "../EP_Game/Bubble.h"

ColliderComponent::ColliderComponent(int width, int height, bool isTrigger)
	:m_Width{ width }
	, m_Height{ height }
	, m_IsTrigger{ isTrigger }
	, m_Position{ glm::vec3(0.f, 0.f, 0.f) }
	, m_JustTriggered{ true }
	, m_IsInTrigger{ false }
	, m_ShouldExit{ false }
{
	m_Shape = { (int)m_Position.x, (int)m_Position.y, m_Width, m_Height };

	ep::CollisionManager::GetInstance().AddCollision(this);
}

void ColliderComponent::Update(const GameTime&)
{
	if (m_pGameObject->GetWidth() == 0 && m_pGameObject->GetHeight() == 0)
	{
		m_pGameObject->SetWidth(m_Width);
		m_pGameObject->SetHeight(m_Height);
	}

	m_Position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();

	//This is due to the coordinate system (0, 0 : top left corner)
	m_Position.x -= m_Width / 2;
	m_Position.y -= m_Height / 2;

	m_Shape.x = (int)m_Position.x;
	m_Shape.y = (int)m_Position.y;
}

void ColliderComponent::Render(const GameTime&)
{
	//ep::Renderer::GetInstance().RenderRectangle(m_Shape, glm::vec3(1.f, 0.f, 0.f));
}

void ColliderComponent::FlagForDelete()
{
	m_IsFlaggedForDelete = true;
}

bool ColliderComponent::IsFlaggedForDelete() const
{
	return m_IsFlaggedForDelete;
}

void ColliderComponent::CheckCollision(ColliderComponent* pOtherCollision)
{
	if (pOtherCollision->m_pGameObject == this->m_pGameObject)
		return;
	
	if (pOtherCollision->m_Position.x < m_Position.x + m_Width && pOtherCollision->m_Position.x + pOtherCollision->m_Width > m_Position.x)
		if (pOtherCollision->m_Position.y < m_Position.y + m_Height && pOtherCollision->m_Position.y + pOtherCollision->m_Height > m_Position.y)
		{
			//ep::Logger::GetInstance().Log("Jup something got definitely hit...");
			if (m_IsTrigger == false)
			{
				OnCollision(pOtherCollision->m_pGameObject);
			}
			else if (m_JustTriggered)
			{
				OnTrigger(pOtherCollision->m_pGameObject);
			}

			//if(m_pTriggeredGameObject == nullptr)
			//{ 
			//	m_JustTriggered = true;
			//	m_pTriggeredGameObject = nullptr;
			//	OnTriggerExit();
			//}

			return;
		}

	if (!m_IsTrigger)
		return;

	//if (m_JustTriggered == false && m_ShouldExit && m_pTriggeredGameObject == nullptr)


	if (m_JustTriggered == false && pOtherCollision->m_pGameObject == m_pTriggeredGameObject)
	{
		m_JustTriggered = true;
		m_pTriggeredGameObject = nullptr;
		OnTriggerExit();
	}
}

void ColliderComponent::Exit()
{
	m_JustTriggered = true;
	m_pTriggeredGameObject = nullptr;
	OnTriggerExit();
}


void ColliderComponent::SetCollisionCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> lambda)
{
	if (m_IsTrigger)
	{
		ep::Logger::GetInstance().Error("{__ColliderComponent::SetCollisionCallBack__} You're assigning a collision callback to a Trigger!");
		return;
	}

	CallBack = lambda;
}

void ColliderComponent::SetTriggerCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> lambda)
{
	if (!m_IsTrigger)
	{
		ep::Logger::GetInstance().Error("{__ColliderComponent::SetTriggerCallBack__} You're assigning a trigger callback to a Collider!");
		return;
	}

	CallBack = lambda;
}

void ColliderComponent::SetTriggerExitCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * POther)> lambda)
{
	if (!m_IsTrigger)
	{
		ep::Logger::GetInstance().Error("{__ColliderComponent::SetTriggerExitCallBack__} You're assigning a trigger callback to a Collider!");
		return;
	}

	ExitCallBack = lambda;
}

void ColliderComponent::OnCollision(ep::GameObject* pOtherCollision)
{
	if (CallBack)
		CallBack(this->m_pGameObject, pOtherCollision);
}

void ColliderComponent::OnTrigger(ep::GameObject* pOtherCollision)
{
	if (CallBack)
	{
		CallBack(this->m_pGameObject, pOtherCollision);
		m_JustTriggered = false;
		m_pTriggeredGameObject = pOtherCollision;
		m_ShouldExit = true;
	}
}

void ColliderComponent::OnTriggerExit()
{
	if (ExitCallBack)
	{
		ExitCallBack(this->m_pGameObject, nullptr);
	}
}
