#include "EP_Engine_PCH.h"
#include "FontComponent.h"
#include "TextObject.h"
#include "ResourceManager.h"
#include <SDL_ttf.h>
#include "Renderer.h"

#include "Texture2D.h"
#include "Font.h"

FontComponent::FontComponent(glm::vec3 pos, const std::string& fontName, unsigned int size, const std::string& text)
	:m_PosX{ pos.x }
	, m_PosY{ pos.y }
	, m_Color{ (Uint8)255.f, (Uint8)255.f, (Uint8)255.f, (Uint8)255.f }
	, m_IsVarChanged{ true }
{
	m_pFont = ep::ResourceManager::GetInstance().LoadFont(fontName, size);
	m_Text = text;


	TextureCreation();
}

FontComponent::~FontComponent()
{
	SafeDelete(m_pTexture);
	SafeDelete(m_pFont);
}

void FontComponent::Update(const GameTime&)
{
	if (m_IsVarChanged)
	{
		TextureCreation();
		m_IsVarChanged = false;
	}
}

void FontComponent::Render(const GameTime&)
{
	if (m_pTexture != nullptr)
	{
		ep::Renderer::GetInstance().RenderTexture(*m_pTexture, m_PosX, m_PosY);
	}
}

void FontComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_IsVarChanged = true;
}

void FontComponent::SetFont(const std::string& fontName, const unsigned int size)
{
	m_pFont = ep::ResourceManager::GetInstance().LoadFont(fontName, size);
	m_IsVarChanged = true;
}

void FontComponent::SetPosition(float x, float y)
{
	m_PosX = x;
	m_PosY = y;
	m_IsVarChanged = true;
}

void FontComponent::SetColor(float r, float g, float b, float a)
{
	m_Color = { (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a };
	m_IsVarChanged = true;
}

void FontComponent::TextureCreation()
{
	SDL_Surface* surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(ep::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	//If not deleted and set to nullptr, this gives memory leaks and throws an exception
	SafeDelete(m_pTexture);
	m_pTexture = new ep::Texture2D(texture);
}
