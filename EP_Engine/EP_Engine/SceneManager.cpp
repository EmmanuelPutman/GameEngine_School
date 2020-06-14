#include "SceneManager.h"
#include "EP_Engine_PCH.h"
#include "SceneManager.h"
#include "Scene.h"

void ep::SceneManager::Update(const GameTime& gameTime)
{
	m_pScene->Update(gameTime);
	
}

void ep::SceneManager::Render(const GameTime& gameTime)
{
	m_pScene->Render(gameTime);
	
}

ep::SceneManager::~SceneManager()
{
	SafeDelete(m_pScene);
}

ep::Scene* ep::SceneManager::CreateScene(const std::string& name)
{
	auto scene = new Scene(name);
	m_pScene = scene;
	return scene;
}

