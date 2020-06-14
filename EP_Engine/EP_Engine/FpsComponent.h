#pragma once
#include "Component.h"
class FontComponent;

class FpsComponent : public ep::Component
{
public:
	FpsComponent(const std::string& fontPath, unsigned int size, const std::string& text);
	~FpsComponent() override;
	FpsComponent(const FpsComponent&) = delete;
	FpsComponent(FpsComponent&&) = delete;
	FpsComponent& operator= (const FpsComponent&) = delete;
	FpsComponent& operator= (const FpsComponent&&) = delete;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

private:
	int m_NrOfFrames;
	FontComponent* m_pFontComponent;
	bool m_ShouldInitFontPos;

	float m_Timer;
	int m_FPS;
};

