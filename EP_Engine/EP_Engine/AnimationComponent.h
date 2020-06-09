#pragma once
#include "Component.h"

namespace ep {
	class Texture2D;
}

#include <SDL.h>

class AnimationComponent : public ep::Component
{
public:
	AnimationComponent(const std::string fileName, UINT columns, UINT rows, float spriteSwapAfterS);
	~AnimationComponent();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

private:
	float m_SpriteSwapAfter;
	float m_Timer;

	int m_Width;
	int m_Height;

	int m_FrameWidth;
	int m_FrameHeight;

	ep::Texture2D* m_pTexture;

	SDL_Rect m_SrcRect;
	SDL_Rect m_DestRect;
};

