#include "SceneManager.h"
#include "EP_Engine_PCH.h"
#include "SceneManager.h"
#include "Scene.h"

void ep::SceneManager::Update(const GameTime& gameTime)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(gameTime);
	}
}

void ep::SceneManager::Render(const GameTime& gameTime)
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render(gameTime);
	}
}

ep::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
}

ep::Scene* ep::SceneManager::CreateScene(const std::string& name)
{
	auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return scene;
}

