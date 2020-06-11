#include "EP_Engine_PCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void ep::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void ep::Renderer::Render(const GameTime& gameTime) const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render(gameTime);
	
	SDL_RenderPresent(m_Renderer);
}

void ep::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void ep::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void ep::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void ep::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect dst, SDL_Rect src) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
}

void ep::Renderer::RenderRectangle(const SDL_Rect& shape, const glm::vec3& color) const
{
	SDL_SetRenderDrawColor(GetSDLRenderer(), Uint8(color.x * 255.f), Uint8(color.y * 255.f), Uint8(color.z * 255.f), Uint8(1.f * 255.f));
	
	SDL_RenderDrawRect(GetSDLRenderer(), &shape);

	SDL_SetRenderDrawColor(GetSDLRenderer(), 0, 0, 0, 255);

}
