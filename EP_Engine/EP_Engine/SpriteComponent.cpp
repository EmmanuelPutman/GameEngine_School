#include "EP_Engine_PCH.h"
#include "SpriteComponent.h"

#include "Texture2D.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include "GameObject.h"

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
	//if (m_pGameObject->GetWidth() == 0 && m_pGameObject->GetHeight() == 0)
	//{
	//	m_pGameObject->SetWidth(m_Width);
	//	m_pGameObject->SetHeight(m_Height);
	//}
}

void SpriteComponent::Render(const GameTime&)
{
	//This is due to the coordinate system (0, 0 : top left corner)
	m_PosX = GetTransform()->GetPosition().x - m_Width /2;
	m_PosY = GetTransform()->GetPosition().y - m_Height /2;
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
