#pragma once
#include "Component.h"
namespace ep
{
	class Texture2D;
}
#include <string>
#include <memory>

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

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
	std::shared_ptr<ep::Texture2D> m_pTexture;
	float m_PosX;
	float m_PosY;
};

