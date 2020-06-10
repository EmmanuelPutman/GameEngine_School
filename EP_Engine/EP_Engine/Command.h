#pragma once
#include <iostream>
#include "Audio.h"
#include "Logger.h"
using namespace ep;

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	Command(const Command&) = delete;
	Command(Command&&) = delete;
	Command& operator= (const Command&) = delete;
	Command& operator= (const Command&&) = delete;

	virtual void Execute(const GameTime& gameTime) = 0;
	//const std::string& GetName() const { return m_Name; };
	//void SetName(const std::string& name) { m_Name = name; };

protected:
	//std::string m_Name;
};

