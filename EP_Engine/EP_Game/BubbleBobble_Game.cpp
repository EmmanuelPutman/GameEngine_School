#include "EP_Engine_PCH.h"
#include "BubbleBobble_Game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "GameCommands.h"
#include "Logger.h"

#include "GameObject.h"
//#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "FpsComponent.h"

using namespace ep;

BubbleBobble_Game::BubbleBobble_Game(const GameTime& gameTime)
{
	Initialize(gameTime);
}

BubbleBobble_Game::~BubbleBobble_Game()
{
}

void BubbleBobble_Game::Initialize(const GameTime& gameTime)
{
	m_pScene = ep::SceneManager::GetInstance().CreateScene("BubbleBobble");

	GameObject* pGoFPS = new GameObject();
	TransformComponent* pFpsTrans = new TransformComponent();
	pFpsTrans->ChangePositionTo(gameTime.WindowWidth / 2.f - 10.f, gameTime.WindowHeight - 9.f, 0.f);
	pGoFPS->AddComponent(pFpsTrans);
	FpsComponent* pFPS = new FpsComponent("Lingua.otf", 13, "00 FPS");
	pGoFPS->AddComponent(pFPS);
	m_pScene->Add(pGoFPS);

#pragma region CharacterTEST

	character = new GameObject();
	TransformComponent* pTransform = new TransformComponent();
	pTransform->ChangePositionTo(300.f, 0.f, 0.f);
	character->AddComponent(pTransform);

	AnimationComponent* pAnim = new AnimationComponent("CharacterRun.png", 7, 1, 0.09f);
	character->AddComponent(pAnim);

	ColliderComponent* pCollider = new ColliderComponent(pAnim->GetFrameWidth(), pAnim->GetFrameWidth());
	character->AddComponent(pCollider);

	m_pScene->Add(character);

	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyA, new MoveLeftCommand(character));
	InputManager::GetInstance().SetCommandToButton(ep::KeyboardKey::KeyD, new MoveRightCommand(character));

#pragma endregion
	
#pragma region WallTEST

	GameObject* pWall = new GameObject();
	TransformComponent* pWallTrans = new TransformComponent();
	pWallTrans->ChangePositionTo(gameTime.WindowWidth / 2.f, gameTime.WindowHeight / 2.f, 0.f);
	pWall->AddComponent(pWallTrans);

	SpriteComponent* pSprite = new SpriteComponent("logo.png");
	pWall->AddComponent(pSprite);

	ColliderComponent* pWallColl = new ColliderComponent(pSprite->GetWidth(), pSprite->GetHeight());
	pWall->AddComponent(pWallColl);

	auto wallCollision = [](GameObject* pThis, GameObject* pOther)
	{
		if (pOther != nullptr && pOther != pThis)
		{
			//Logger::GetInstance().Log("THE WALL GOT HIT!!");
			pOther->GetComponent<TransformComponent>()->AddToPosition(0.0f, -0.2f, 0.f);
		}
	};

	pWall->GetComponent<ColliderComponent>()->SetCollisionCallBack(wallCollision);

	m_pScene->Add(pWall);

#pragma endregion

}

void BubbleBobble_Game::Update(const GameTime& gameTime)
{
	ep::CollisionManager::GetInstance().Update();
	character->GetComponent<TransformComponent>()->AddToPosition(0.f, 9.18f * gameTime.elapsedSec, 0.f);
}
