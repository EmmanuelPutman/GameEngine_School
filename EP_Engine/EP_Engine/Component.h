#pragma once

class TransformComponent;
namespace ep
{
	class GameObject;

	class Component
	{
		friend class GameObject;

	public:
		Component();
		virtual ~Component() = default;
		Component(const Component&) = delete;
		Component(Component&&) = delete;
		Component& operator= (const Component&) = delete;
		Component& operator= (const Component&&) = delete;

		virtual void Update(const GameTime& gameTime) = 0;
		virtual void Render(const GameTime& gameTime) = 0;


	protected:
		TransformComponent* GetTransform() const;
		GameObject* m_pGameObject;

	};
}


