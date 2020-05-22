#include "EP_Engine_PCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int ep::Scene::m_IdCounter = 0;

ep::Scene::Scene(const std::string& name) : m_Name(name) {}

ep::Scene::~Scene() 
{ 
	for (SceneObject* obj : m_Objects)
	{
		SafeDelete(obj);
	}
}

void ep::Scene::Add(SceneObject* object)
{
	m_Objects.push_back(object);
}

void ep::Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void ep::Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}
