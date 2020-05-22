#include "EP_Engine_PCH.h"
#include "Texture2D.h"
#include <SDL.h>

ep::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* ep::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

ep::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
