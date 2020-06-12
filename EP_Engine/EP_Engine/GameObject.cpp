#include "EP_Engine_PCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

using namespace ep;

ep::GameObject::~GameObject() 
{
	for (Component* pComponent : m_pComponents)
	{
		SafeDelete(pComponent);
	}
}

void ep::GameObject::Update(const GameTime& gameTime)
{
	for (auto component : m_pComponents)
		component->Update(gameTime);

}

void ep::GameObject::Render(const GameTime& gameTime) const
{
	for (auto component : m_pComponents)
	{
		component->Render(gameTime);
	}
}

void ep::GameObject::AddComponent(Component* component)
{
	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}
