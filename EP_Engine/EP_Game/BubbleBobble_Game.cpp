#include "EP_Engine_PCH.h"
#include "BubbleBobble_Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Logger.h"

using namespace ep;

BubbleBobble_Game::BubbleBobble_Game()
{
	Initialize();
}

BubbleBobble_Game::~BubbleBobble_Game()
{
}

void BubbleBobble_Game::Initialize()
{
	m_pScene = ep::SceneManager::GetInstance().CreateScene("BubbleBobble");

	character = new GameObject();
	TransformComponent* pTransform = new TransformComponent();
	pTransform->ChangePositionTo(300.f, 0.f, 0.f);
	character->AddComponent(pTransform);

	AnimationComponent* pAnim = new AnimationComponent("CharacterRun.png", 7, 1, 0.09f);
	character->AddComponent(pAnim);

	m_pScene->Add(character);
}

void BubbleBobble_Game::Update(const GameTime& gameTime)
{
	glm::vec3 currPos = character->GetComponent<TransformComponent>()->GetPosition();

	currPos.x -= 10.f * gameTime.elapsedSec;
	character->GetComponent<TransformComponent>()->ChangePositionTo(currPos.x, currPos.y, currPos.z);
	Logger::GetInstance().Error(std::to_string(currPos.x));
}
