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
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (auto component : m_pComponents)
	{
		component->Render(gameTime);
	}
}

void ep::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void ep::GameObject::AddComponent(Component* component)
{
	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}
