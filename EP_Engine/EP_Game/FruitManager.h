#pragma once
namespace ep {
	class GameObject;
}

class FruitManager
{
public:
	FruitManager();
	~FruitManager();
	FruitManager(const FruitManager&) = delete;
	FruitManager(FruitManager&&) = delete;
	FruitManager& operator= (const FruitManager&) = delete;
	FruitManager& operator= (const FruitManager&&) = delete;

	void Update();
	void AddFruit(ep::GameObject* fruit);
	int GetScore() const;

private:
	std::vector<ep::GameObject*> m_pFruits;
	int m_Score;
};

