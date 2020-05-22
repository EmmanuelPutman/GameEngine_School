#include "EP_Engine_PCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

ep::GameObject::~GameObject() 
{
	for (Component* pComponent : m_pComponents)
	{
		SafeDelete(pComponent);
	}
}

void ep::GameObject::Update()
{
	for (auto component : m_pComponents)
		component->Update();

}

void ep::GameObject::Render() const
{
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (auto component : m_pComponents)
	{
		component->Render();
	}
}

void ep::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
