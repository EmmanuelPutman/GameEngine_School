#pragma once

class TransformComponent;

namespace ep
{
	class GameObject;

	class Component
	{

	public:
		Component();
		virtual ~Component() = default;

		virtual void Update(const GameTime& gameTime) = 0;
		virtual void Render(const GameTime& gameTime) = 0;

		GameObject* m_pGameObject;

	protected:
		TransformComponent* GetTransform() const;

	};
}


