#pragma once
#include "Component.h"

#include <string>
#include <memory>

namespace ep {
	class Texture2D;
}

class SpriteComponent :	public ep::Component
{
public:
	SpriteComponent(const std::string fileName);
	~SpriteComponent() override;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;
	void SetTexture(const std::string& filename);

	int GetWidth() const;
	int GetHeight() const;

private:
	ep::Texture2D* m_pTexture;
	float m_PosX;
	float m_PosY;

	int m_Width;
	int m_Height;
};

