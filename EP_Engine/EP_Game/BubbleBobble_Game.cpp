#include "EP_Engine_PCH.h"
#include "BubbleBobble_Game.h"

#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "GameCommands.h"
#include "Logger.h"

#include "GameObject.h"
#include "Character.h"

//#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "ColliderComponent.h"
#include "FpsComponent.h"

#include "PlayerCharacter.h"
#include "Enemy_ZenChan.h"

#include "LevelParser_Pyxel.h"
#include "EnemyManager.h"

using namespace ep;

BubbleBobble_Game::BubbleBobble_Game(const GameTime& gameTime)
{
	Initialize(gameTime);
}

BubbleBobble_Game::~BubbleBobble_Game()
{
	SafeDelete(m_pParser);
	SafeDelete(m_pEnemySpawner);
}

void BubbleBobble_Game::Initialize(const GameTime& gameTime)
{
	m_pScene = ep::SceneManager::GetInstance().CreateScene("BubbleBobble");

#pragma region LevelParseTest

	m_pParser = new LevelParser_Pyxel("Level_1.txt");
	CreateLevel();

#pragma endregion

#pragma region FPS
	
	GameObject* pGoFPS = new GameObject();
	TransformComponent* pFpsTrans = new TransformComponent();
	pFpsTrans->ChangePositionTo(gameTime.WindowWidth / 2.f - 20.f, 15.f, 0.f);
	pGoFPS->AddComponent(pFpsTrans);
	FpsComponent* pFPS = new FpsComponent("Lingua.otf", 13, "00 FPS");
	pGoFPS->AddComponent(pFPS);
	m_pScene->Add(pGoFPS);
	
#pragma endregion

#pragma region Character

	character = new PlayerCharacter(55.f);
	character->GetComponent<TransformComponent>()->ChangePositionTo(300.f, 150.f, 0.f);
	m_pScene->Add(character);

	m_pEnemySpawner = new EnemyManager();

#pragma endregion

	/*
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
			//Logger::GetInstance().Log("I dealt DAMAGE");
			glm::vec3 currPos = pOther->GetComponent<TransformComponent>()->GetPosition();
			pOther->GetComponent<TransformComponent>()->ChangePositionTo(currPos.x, pThis->GetComponent<TransformComponent>()->GetPosition().y - pOther->GetComponent<AnimationComponent>()->GetFrameHeight(), 0.f);
		}
	};

	pWall->GetComponent<ColliderComponent>()->SetCollisionCallBack(wallCollision);

	m_pScene->Add(pWall);

#pragma endregion
	*/

}

void BubbleBobble_Game::Update(const GameTime&)
{
	m_pEnemySpawner->Update();
	ep::CollisionManager::GetInstance().Update();
}

void BubbleBobble_Game::CreateLevel()
{
	for (const std::pair<glm::vec3, int>& block : m_pParser->GetBlocks())
	{
		if (block.second != 0)
		{
			GameObject* pBlock = new GameObject();

			TransformComponent* pTransform = new TransformComponent();
			pTransform->ChangePositionTo(block.first.x, block.first.y, block.first.z);
			pBlock->AddComponent(pTransform);
			std::string tileName = "tile_" + std::to_string(block.second) + ".png";
			SpriteComponent* pSprite = new SpriteComponent(tileName);
			pBlock->AddComponent(pSprite);

			ColliderComponent* pCollision = new ColliderComponent(m_pParser->GetBlockWidth(), m_pParser->GetBlockHeight());
			pBlock->AddComponent(pCollision);

			pBlock->SetTag("Block");

			m_pScene->Add(pBlock);
		}
	}
}
