#include "EP_Engine_PCH.h"
#include "SpriteComponent.h"
#include "Texture2D.h"

#include "ResourceManager.h"
#include "Renderer.h"

SpriteComponent::~SpriteComponent()
{
	SafeDelete(m_pTexture);
}

void SpriteComponent::Update(const GameTime&)
{
}

void SpriteComponent::Render(const GameTime&)
{
	ep::Renderer::GetInstance().RenderTexture(*m_pTexture, m_PosX, m_PosY);
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ep::ResourceManager::GetInstance().LoadTexture(filename);
}

void SpriteComponent::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
}
