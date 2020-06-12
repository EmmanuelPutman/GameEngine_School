#pragma once
#include "Singleton.h"

namespace ep
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager() = default;
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator= (const SceneManager&) = delete;
		SceneManager& operator= (const SceneManager&&) = delete;

		Scene* CreateScene(const std::string& name);
		void Update(const GameTime& gameTime);
		void Render(const GameTime& gameTime);

		Scene* GetScene() { return m_Scenes[0]; };

	private:
		std::vector<Scene*> m_Scenes;
	};
}
