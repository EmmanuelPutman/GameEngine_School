#include "EP_Engine_PCH.h"
#include "FpsComponent.h"

#include "FontComponent.h"
#include "Renderer.h"
#include "Logger.h"

FpsComponent::FpsComponent(const std::string& fontPath, unsigned int size, const std::string& text)
	:m_NrOfFrames{ 0 }
{
	m_pFontComponent = new FontComponent(fontPath, size, text);
}

FpsComponent::~FpsComponent()
{
	SafeDelete(m_pFontComponent);
}

void FpsComponent::Update(const GameTime& gameTime)
{
	m_pFontComponent->Update(gameTime);
}

void FpsComponent::Render(const GameTime& gameTime)
{
	m_pFontComponent->SetColor(255.f, 0.f, 0.f, 1.f);
	m_pFontComponent->SetText(std::to_string(gameTime.FPS) + " FPS");
	m_pFontComponent->Render(gameTime);
}
