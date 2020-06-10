#include "EP_Engine_PCH.h"
#include "SpriteComponent.h"

#include "Texture2D.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>

SpriteComponent::SpriteComponent(const std::string fileName)
	:m_pTexture{ nullptr }
	, m_PosX{ 0.f }
	, m_PosY{ 0.f}
	, m_Width{ 0 }
	, m_Height{ 0 }
{
	m_pTexture = ep::ResourceManager::GetInstance().LoadTexture(fileName);
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}

SpriteComponent::~SpriteComponent()
{
	SafeDelete(m_pTexture); 
}

void SpriteComponent::Update(const GameTime&)
{
}

void SpriteComponent::Render(const GameTime&)
{
	m_PosX = GetTransform()->GetPosition().x;
	m_PosY = GetTransform()->GetPosition().y;
	ep::Renderer::GetInstance().RenderTexture(*m_pTexture, m_PosX, m_PosY);
}

void SpriteComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ep::ResourceManager::GetInstance().LoadTexture(filename);

	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);
}

int SpriteComponent::GetWidth() const
{
	return m_Width;
}

int SpriteComponent::GetHeight() const
{
	return m_Height;
}
