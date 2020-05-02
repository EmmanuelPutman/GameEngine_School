#pragma once
#include "SceneManager.h"

namespace ep
{
	class SceneObject;
	class Scene
	{
		friend ep::Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update();
		void Render() const;

		std::shared_ptr<SceneObject> GetSceneObject();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
