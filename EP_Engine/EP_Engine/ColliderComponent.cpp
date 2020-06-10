#include "EP_Engine_PCH.h"
#include "ColliderComponent.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"

#include "Renderer.h"
#include "Logger.h"
#include "CollisionManager.h"

ColliderComponent::ColliderComponent(int width, int height, bool isTrigger)
	:m_Width{ width }
	, m_Height{ height }
	, m_IsTrigger{ isTrigger }
	,m_Position{ glm::vec3(0.f, 0.f, 0.f) }
{
	m_Shape = { (int)m_Position.x, (int)m_Position.y, m_Width, m_Height };
	
	ep::CollisionManager::GetInstance().AddCollision(this);
}

void ColliderComponent::Update(const GameTime&)
{
	m_Position = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
	m_Shape.x = (int)m_Position.x;
	m_Shape.y = (int)m_Position.y;
}

void ColliderComponent::Render(const GameTime&)
{
	ep::Renderer::GetInstance().RenderRectangle(m_Shape, glm::vec3(1.f, 0.f, 0.f));
}

void ColliderComponent::CheckCollision(ColliderComponent* pOtherCollision)
{
	if (pOtherCollision->m_Position.x < m_Position.x + m_Width && pOtherCollision->m_Position.x + pOtherCollision->m_Width > m_Position.x)
		if (pOtherCollision->m_Position.y < m_Position.y + m_Height && pOtherCollision->m_Position.y + pOtherCollision->m_Height > m_Position.y)
		{
			//ep::Logger::GetInstance().Log("Jup something got definitely hit...");
			if(m_IsTrigger == false)
			{ 
				OnCollision(pOtherCollision->m_pGameObject);
			}
			else if(m_JustTriggered)
			{
				OnTrigger(pOtherCollision->m_pGameObject);
			}

			return;
		}

	if(m_JustTriggered == false)
		m_JustTriggered = true;
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

void ColliderComponent::OnCollision(ep::GameObject* pOtherCollision)
{
	if(CallBack)
		CallBack(this->m_pGameObject, pOtherCollision);
}

void ColliderComponent::OnTrigger(ep::GameObject* pOtherCollision)
{
	if(CallBack)
	{ 
		CallBack(this->m_pGameObject, pOtherCollision);
		m_JustTriggered = false;
	}
}
