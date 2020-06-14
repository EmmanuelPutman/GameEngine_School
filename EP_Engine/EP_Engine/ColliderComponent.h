#pragma once
#include "Component.h"
#include <SDL.h>

#include <functional>

class ColliderComponent : public ep::Component
{
public:
	ColliderComponent(int width, int height, bool isTrigger = false);
	~ColliderComponent() override = default;
	ColliderComponent(const ColliderComponent&) = delete;
	ColliderComponent(ColliderComponent&&) = delete;
	ColliderComponent& operator= (const ColliderComponent&) = delete;
	ColliderComponent& operator= (const ColliderComponent&&) = delete;

	void Update(const GameTime& gameTime) override;
	void Render(const GameTime& gameTime) override;

	void FlagForDelete();
	bool IsFlaggedForDelete() const;

	void CheckCollision(ColliderComponent* pOtherCollision);
	void Exit();

	void SetCollisionCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> lambda);
	void SetTriggerCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> lambda);
	void SetTriggerExitCallBack(std::function<void(ep::GameObject * pThis, ep::GameObject * POther)> lambda);

private:
	int m_Width;
	int m_Height;

	SDL_Rect m_Shape;
	glm::vec3 m_Position;

	bool m_IsTrigger;
	bool m_JustTriggered;
	bool m_IsInTrigger;
	bool m_ShouldExit;
	ep::GameObject* m_pTriggeredGameObject;

	bool m_IsFlaggedForDelete;

	void OnCollision(ep::GameObject* pOtherCollision);
	void OnTrigger(ep::GameObject* pOtherCollision);
	void OnTriggerExit();

	std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> CallBack;
	std::function<void(ep::GameObject * pThis, ep::GameObject * pOther)> ExitCallBack;
};

