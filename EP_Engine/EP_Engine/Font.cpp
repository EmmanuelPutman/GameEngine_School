#include "EP_Engine_PCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* ep::Font::GetFont() const {
	return m_Font;
}

ep::Font::Font(const std::string& fullPath, unsigned int size) : m_Font(nullptr), m_Size(size)
{
	m_Font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_Font == nullptr) 
	{
		std::cout << "FAILED to load FONT: " + fullPath;
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

ep::Font::~Font()
{
	TTF_CloseFont(m_Font);
}
