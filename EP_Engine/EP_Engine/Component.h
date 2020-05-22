#pragma once
class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:

};


