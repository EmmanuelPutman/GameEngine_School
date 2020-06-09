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
	SpriteComponent() { m_pTexture = nullptr; m_PosX = 0.f; m_PosY = 0.f; };
	~SpriteComponent() override;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;
	void SetTexture(const std::string& filename);
	void SetPosition(float x, float y);

private:
	ep::Texture2D* m_pTexture;
	float m_PosX;
	float m_PosY;
};

