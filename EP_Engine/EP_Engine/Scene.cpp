#include "Scene.h"
#include "Scene.h"
#include "EP_Engine_PCH.h"
#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

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

void ep::Scene::Remove(SceneObject* pObject)
{
	//No instant remove, bcs we're still looping over a vector in update. NEVER change a vector while iterating over it!
	m_ObjectsToRemove.push_back(pObject);
}

void ep::Scene::Update(const GameTime& gameTime)
{
	for(auto& object : m_Objects)
	{
		if (object)
			object->Update(gameTime);
		else
			SafeDelete(object);
	}

	//Remove the object after the update loop is done
	for (auto& object : m_ObjectsToRemove)
	{
		auto it = std::remove(m_Objects.begin(), m_Objects.end(), object);
		m_Objects.erase(it);
		SafeDelete(object);
	}

	m_ObjectsToRemove.clear();
}

void ep::Scene::Render(const GameTime& gameTime) const
{
	for (const auto& object : m_Objects)
	{
		object->Render(gameTime);
	}
}

std::vector<ep::SceneObject*> ep::Scene::GetSceneObjects()
{
	return m_Objects;
}



