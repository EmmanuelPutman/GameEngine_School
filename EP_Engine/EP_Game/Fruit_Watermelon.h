#pragma once
#include "Fruit.h"
class Fruit_Watermelon : public Fruit
{
public:
	Fruit_Watermelon(const glm::vec3& pos);
	~Fruit_Watermelon();
	Fruit_Watermelon(const Fruit_Watermelon&) = delete;
	Fruit_Watermelon(Fruit_Watermelon&&) = delete;
	Fruit_Watermelon& operator= (const Fruit_Watermelon&) = delete;
	Fruit_Watermelon& operator= (const Fruit_Watermelon&&) = delete;

private:

};

