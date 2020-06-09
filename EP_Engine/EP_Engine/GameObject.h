#pragma once
#include "Transform.h"
#include "SceneObject.h"

namespace ep
{
	class Component;
	class Texture2D;

	class GameObject : public SceneObject
	{
	public:
		void Update(const GameTime& gameTime) override;
		void Render(const GameTime& gameTime) const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template<class T>
		T* GetComponent();

		void AddComponent(Component* component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;

		std::vector<Component*> m_pComponents;
	};

	template<class T>
	inline T* GameObject::GetComponent()
	{
		for (auto component : m_pComponents)
		{
			if(component != nullptr && typeid(*component) == typeid(T))
				return static_cast<T*>(component);
		}

		return nullptr;
	}

}
