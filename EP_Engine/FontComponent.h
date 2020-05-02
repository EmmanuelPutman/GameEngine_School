#pragma once
#include "Component.h"
#include <memory>
#include <string>
#include <SDL.h>
namespace ep{
	class TextObject;
	class Texture2D;
	class Font;
}

class FontComponent : public Component
{
public:
	FontComponent(const std::string& fontName, unsigned int size, const std::string& text);
	~FontComponent();
	
	void Update() override;
	void Render() override;

	void SetText(const std::string& text);
	void SetFont(const std::string& fontName, const unsigned int size);
	void SetPosition(float x, float y);
	void SetColor(float r, float g, float b, float a);

	void TextureCreation();

private:
	std::shared_ptr<ep::Texture2D> m_pTexture;
	std::shared_ptr<ep::Font> m_pFont;
	std::string m_Text;
	float m_PosX;
	float m_PosY;
	SDL_Color m_Color;

	bool m_IsVarChanged;
};
