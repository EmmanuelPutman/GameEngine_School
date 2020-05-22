#pragma once
#include "Component.h"

#include <string>
#include <memory>

namespace ep {
	class Texture2D;
}

class RenderComponent :	public Component
{
public:
	RenderComponent() { m_pTexture = nullptr; m_PosX = 0.f; m_PosY = 0.f; };
	~RenderComponent() override;

	void Update() override;
	void Render() override;
	void SetTexture(const std::string& filename);
	void SetPosition(float x, float y);

private:
	ep::Texture2D* m_pTexture;
	float m_PosX;
	float m_PosY;
};

