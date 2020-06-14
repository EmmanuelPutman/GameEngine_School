#pragma once
#include "SceneManager.h"

namespace ep
{
	class SceneObject;
	class Scene
	{
		friend ep::Scene* SceneManager::CreateScene(const std::string& name);
	public:
		void Add(SceneObject* object);
		void Remove(SceneObject* pObject);

		void Update(const GameTime& gameTime);
		void Render(const GameTime& gameTime) const;

		std::vector<SceneObject*> GetSceneObjects();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <SceneObject*> m_Objects{};
		std::vector<SceneObject*> m_ObjectsToRemove{};

		static unsigned int m_IdCounter; 
	};

}
