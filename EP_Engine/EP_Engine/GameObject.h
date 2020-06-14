#pragma once
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

		int GetWidth() const { return m_Width; };
		int GetHeight() const { return m_Height; };
		void SetWidth(int width) { m_Width = width; };
		void SetHeight(int height) { m_Height = height; };

		template<class T>
		T* GetComponent();

		template<class T>
		std::vector<T*> GetComponents();

		void AddComponent(Component* component);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const std::string& GetTag() const { return m_Tag; };
		void SetTag(const std::string& tag) { m_Tag = tag; };

	protected:
		std::string m_Tag = "";
		int m_Width = 0;
		int m_Height = 0;

	private:
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

	template<class T>
	inline std::vector<T*> GameObject::GetComponents()
	{
		std::vector<T*> components{};
		for (auto component : m_pComponents)
		{
			if (component != nullptr && typeid(*component) == typeid(T))
				components.push_back(static_cast<T*>(component));
		}

		return components;
	}
}
