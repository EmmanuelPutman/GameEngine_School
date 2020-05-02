#include "EP_Engine_PCH.h"
#include "RenderComponent.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Render()
{
	ep::Renderer::GetInstance().RenderTexture(*m_pTexture, m_PosX, m_PosY);
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ep::ResourceManager::GetInstance().LoadTexture(filename);
}

void RenderComponent::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}
