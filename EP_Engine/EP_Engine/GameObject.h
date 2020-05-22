#pragma once
#include "Transform.h"
#include "SceneObject.h"
class Component;

namespace ep
{
	class Texture2D;
	class GameObject : public SceneObject
	{
	public:
		void Update() override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		template<class T>
		T GetComponent();

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
	inline T GameObject::GetComponent()
	{
		for (auto component : m_pComponents)
		{
			if(typeid(component) == typeid(T))
				return component;
		}
	}

	inline void GameObject::AddComponent(Component* component)
	{
		m_pComponents.push_back(component);
	}
}
