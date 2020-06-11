#include "EP_Engine_PCH.h"
#include "AnimationComponent.h"

#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
#include "TransformComponent.h"
#include "GameObject.h"

AnimationComponent::AnimationComponent(const std::string fileName, UINT columns, UINT rows, float spriteSwapAfterS)
	:m_Width{ 0 }
	, m_Height{ 0 }
	, m_SpriteSwapAfter{ spriteSwapAfterS }
	, m_Timer{ 0.f }
{
	m_pTexture = ep::ResourceManager::GetInstance().LoadTexture(fileName);
	SDL_QueryTexture(m_pTexture->GetSDLTexture(), nullptr, nullptr, &m_Width, &m_Height);

	m_FrameWidth = m_Width / columns;
	m_FrameHeight = m_Height / rows;
	m_SrcRect = { 0, 0, (int)m_FrameWidth, (int)m_FrameHeight };
	m_DestRect = { 0, 0, (int)m_FrameWidth, (int)m_FrameWidth };

}

AnimationComponent::~AnimationComponent()
{
	SafeDelete(m_pTexture);
}

void AnimationComponent::Update(const GameTime& gameTime)
{
	if (m_pGameObject->GetWidth() == 0 && m_pGameObject->GetHeight() == 0)
	{
		m_pGameObject->SetWidth(m_FrameWidth);
		m_pGameObject->SetHeight(m_FrameHeight);
	}

	int pixelOffset = 2; //else he could just have this 1px offset and show a black screen

	glm::vec3 pos = this->GetTransform()->GetPosition();
	//This is due to the coordinate system (0, 0 : top left corner)
	m_DestRect.x = (int)pos.x - m_FrameWidth /2;
	m_DestRect.y = (int)pos.y - m_FrameHeight /2;


	if (m_Timer >= m_SpriteSwapAfter)
	{
		if (m_SrcRect.x + m_FrameWidth + pixelOffset < m_Width)
		{
			m_SrcRect.x += m_FrameWidth;
		}
		else
		{
			m_SrcRect.x = 0;

			if(m_SrcRect.y + m_FrameHeight + pixelOffset < m_Height)
			{ 
				m_SrcRect.y += m_FrameHeight;
			}
			else
			{
				m_SrcRect.y = 0;
			}
		}

		m_Timer = 0.f;
	}

	m_Timer += gameTime.elapsedSec;
}

void AnimationComponent::Render(const GameTime&)
{
	ep::Renderer::GetInstance().RenderTexture(*m_pTexture, m_DestRect, m_SrcRect);
}

int AnimationComponent::GetFrameWidth() const
{
	return m_FrameWidth;
}

int AnimationComponent::GetFrameHeight() const
{
	return m_FrameHeight;
}


