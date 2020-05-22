#include "EP_Engine_PCH.h"
#include "SceneManager.h"
#include "Scene.h"

void ep::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void ep::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

ep::SceneManager::~SceneManager()
{
	for (Scene* pScene : m_Scenes)
	{
		SafeDelete(pScene);
	}
}

ep::Scene& ep::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_Scenes.push_back(scene);
	return *scene;
}
