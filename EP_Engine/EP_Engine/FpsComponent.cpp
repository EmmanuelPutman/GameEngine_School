#include "EP_Engine_PCH.h"
#include "FpsComponent.h"

#include "FontComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Logger.h"

FpsComponent::FpsComponent(const std::string& fontPath, unsigned int size, const std::string& text)
	:m_NrOfFrames{ 0 }
	, m_ShouldInitFontPos{ true }
	, m_Timer{ 0.f }
{
	m_pFontComponent = new FontComponent(glm::vec3(0.f, 0.f, 0.f), fontPath, size, text);
}

FpsComponent::~FpsComponent()
{
	SafeDelete(m_pFontComponent);
}

void FpsComponent::Update(const GameTime& gameTime)
{

	if (m_ShouldInitFontPos)
	{
		m_pFontComponent->SetPosition(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y);
		m_ShouldInitFontPos = false;
	}

	m_pFontComponent->Update(gameTime);

	m_Timer += gameTime.elapsedSec;
}

void FpsComponent::Render(const GameTime& gameTime)
{
	m_pFontComponent->SetColor(255.f, 0.f, 0.f, 1.f);

	if (m_Timer >= 1.f)
	{
		m_FPS = gameTime.FPS;
		m_Timer = 0.f;
	}

	m_pFontComponent->SetText(std::to_string(m_FPS) + " FPS");
	m_pFontComponent->Render(gameTime);

}
