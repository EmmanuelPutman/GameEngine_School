#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Rect;

namespace ep
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render(const GameTime& gameTime) const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		void RenderTexture(const Texture2D& texture, SDL_Rect dst, SDL_Rect src, int direction) ;
		//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, float sourceW, float sourceH) const;

		void RenderRectangle(const SDL_Rect& shape, const glm::vec3& color) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

