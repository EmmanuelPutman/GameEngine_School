#pragma once
namespace ep
{
	class SceneObject
	{
	public:
		virtual void Update(const GameTime& gameTime) = 0;
		virtual void Render(const GameTime& gameTime) const = 0;

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
