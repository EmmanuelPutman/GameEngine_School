#pragma once
#include "Component.h"
class FontComponent;

class FpsComponent : public ep::Component
{
public:
	FpsComponent(const std::string& fontPath, unsigned int size, const std::string& text);
	~FpsComponent();

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

private:
	int m_NrOfFrames;
	FontComponent* m_pFontComponent;
};
