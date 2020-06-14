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
#include "HealthComponent.h"
#include "FontComponent.h"

#include "PlayerCharacter.h"
#include "Enemy_ZenChan.h"

#include "LevelParser_Pyxel.h"
#include "EnemyManager.h"

#include "Fruit.h"
#include "Fruit_Watermelon.h"

using namespace ep;

BubbleBobble_Game::BubbleBobble_Game(const GameTime& gameTime)
	:m_LevelNr{ 1 }
	, m_NextLevelTimer{ 0.f }
	, m_NextLevelAfterS{ 3.f }
	, m_GameOver{ false }
	, m_PrevLevelScore{ 0 }
	, m_Score{ 0 }
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
	CreateLevel(gameTime);

#pragma endregion

#pragma region ObjectsDisplayingText

	GameObject* pGoFPS = new GameObject();
	TransformComponent* pFpsTrans = new TransformComponent();
	pFpsTrans->ChangePositionTo(gameTime.WindowWidth / 2.f - 20.f, 15.f, 0.f);
	pGoFPS->AddComponent(pFpsTrans);
	FpsComponent* pFPS = new FpsComponent("Lingua.otf", 13, "00 FPS");
	pGoFPS->AddComponent(pFPS);
	m_pScene->Add(pGoFPS);

	m_pPlayerLivesObj = new GameObject();
	TransformComponent* pPlayerLivesTransf = new TransformComponent();
	pPlayerLivesTransf->ChangePositionTo(5.f, 10.f, 0.f);
	m_pPlayerLivesObj->AddComponent(pPlayerLivesTransf);
	FontComponent* pLivesFont = new FontComponent("Lingua.otf", 25, "Lives: 4");
	m_pPlayerLivesObj->AddComponent(pLivesFont);
	m_pScene->Add(m_pPlayerLivesObj);

	m_pScoreObj = new GameObject();
	TransformComponent* pScoreTransf = new TransformComponent();
	pScoreTransf->ChangePositionTo(gameTime.WindowWidth - 50.f, 10.f, 0.f);
	m_pScoreObj->AddComponent(pScoreTransf);
	FontComponent* pScoreFont = new FontComponent("Lingua.otf", 25, "000");
	m_pScoreObj->AddComponent(pScoreFont);
	m_pScene->Add(m_pScoreObj);

#pragma endregion

#pragma region Character

	character = new PlayerCharacter(55.f);
	character->GetComponent<TransformComponent>()->ChangePositionTo(300.f, 150.f, 0.f);
	m_pScene->Add(character);

	m_pEnemySpawner = new EnemyManager();

#pragma endregion

#pragma region Sound

	AudioManager::GetInstance().AddSound((int)Commands::FireBubble, "../Resources/BubbleFire.wav");
	AudioManager::GetInstance().AddSound((int)Commands::Jump, "../Resources/Jump.wav");

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

void BubbleBobble_Game::Update(const GameTime& gameTime)
{
	if (m_pEnemySpawner != nullptr)
	{
		m_pEnemySpawner->Update();

		

		if ((m_pEnemySpawner->GetEnemiesAlive() <= 0 && m_LevelNr < 4) || m_GameOver)
		{
			m_NextLevelTimer += gameTime.elapsedSec;


			if (m_NextLevelTimer > m_NextLevelAfterS || m_GameOver)
			{
				m_Score += m_PrevLevelScore;
				
				m_NextLevelTimer = 0.f;

				if (m_GameOver)
				{
					m_LevelNr = 3;
					m_GameOver = false;
					SafeDelete(m_pEnemySpawner);

					m_PrevLevelScore = 0;
				}

				GoToNextLevel(gameTime);
			}
		}

		if(m_pEnemySpawner != nullptr)
			m_PrevLevelScore = m_pEnemySpawner->GetScore();
	}
	if (character->GetComponent<HealthComponent>()->GetHealth() <= 0)
	{
		m_GameOver = true;
	}

	ep::CollisionManager::GetInstance().Update();

	m_pPlayerLivesObj->GetComponent<FontComponent>()->SetText("Lives: " + std::to_string(character->GetComponent<HealthComponent>()->GetHealth()));
	m_pScoreObj->GetComponent<FontComponent>()->SetText(std::to_string(m_Score + m_PrevLevelScore));
}

void BubbleBobble_Game::CreateLevel(const GameTime& gameTime)
{
	GameObject* pFallObject = new GameObject();
	TransformComponent* pFallTrans = new TransformComponent();
	pFallTrans->ChangePositionTo(gameTime.WindowWidth / 2.f, gameTime.WindowHeight + 20.f, 0.f);
	pFallObject->AddComponent(pFallTrans);

	ColliderComponent* pFallCollider = new ColliderComponent(gameTime.WindowWidth, 40, true);
	pFallObject->AddComponent(pFallCollider);

	auto bottomLevelCallBack = [gameTime](ep::GameObject* pThis, ep::GameObject* pOther)
	{
		if (pOther != pThis)
		{
			pOther->GetComponent<TransformComponent>()->ChangePositionTo(pOther->GetComponent<TransformComponent>()->GetPosition().x, 50.f, 0.f);
		}
	};

	pFallCollider->SetTriggerCallBack(bottomLevelCallBack);

	pFallObject->SetTag("Block");
	m_pScene->Add(pFallObject);

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

void BubbleBobble_Game::GoToNextLevel(const GameTime& gameTime)
{
	++m_LevelNr;

	for (ep::SceneObject* pObj : ep::SceneManager::GetInstance().GetScene()->GetSceneObjects())
	{
		if (static_cast<ep::GameObject*>(pObj)->GetTag() == "Block" || static_cast<ep::GameObject*>(pObj)->GetTag() == "Fruit" || static_cast<ep::GameObject*>(pObj)->GetTag() == "Enemy")
		{
			for (ColliderComponent* pCollision : static_cast<ep::GameObject*>(pObj)->GetComponents<ColliderComponent>())
			{
				pCollision->FlagForDelete();
				ep::CollisionManager::GetInstance().RemoveCollision(pCollision);
			}

			ep::SceneManager::GetInstance().GetScene()->Remove(pObj);

		}
	}


#pragma region LevelParseTest

	SafeDelete(m_pParser);

	if (m_LevelNr == 4)
	{
		m_pParser = new LevelParser_Pyxel("TheEnd.txt");
		CreateLevel(gameTime);
		SafeDelete(m_pEnemySpawner);
	}
	else
	{
		//SafeDelete(m_pParser);
		m_pParser = new LevelParser_Pyxel("Level_" + std::to_string(m_LevelNr) + ".txt");
		CreateLevel(gameTime);

		SafeDelete(m_pEnemySpawner);
		m_pEnemySpawner = new EnemyManager();
	}



#pragma endregion

#pragma region Character

	character->GetComponent<HealthComponent>()->Reset();
	character->GetComponent<TransformComponent>()->ChangePositionTo(300.f, 150.f, 0.f);

#pragma endregion
}
