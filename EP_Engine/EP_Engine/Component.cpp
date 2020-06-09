#include "EP_Engine_PCH.h"
#include "Component.h"

#include "GameObject.h"
#include "TransformComponent.h"

using namespace ep;

ep::Component::Component()
	:m_pGameObject{ nullptr }
{
}

TransformComponent* ep::Component::GetTransform() const
{
	if(m_pGameObject != nullptr)
	{ 
		return m_pGameObject->GetComponent<TransformComponent>();
	}

	return nullptr;
}
