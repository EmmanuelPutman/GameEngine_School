#pragma once
#include "Fruit.h"
class Fruit_FrenchFries : public Fruit
{
public:
	Fruit_FrenchFries(const glm::vec3& pos);
	~Fruit_FrenchFries();
	Fruit_FrenchFries(const Fruit_FrenchFries&) = delete;
	Fruit_FrenchFries(Fruit_FrenchFries&&) = delete;
	Fruit_FrenchFries& operator= (const Fruit_FrenchFries&) = delete;
	Fruit_FrenchFries& operator= (const Fruit_FrenchFries&&) = delete;

private:

};

