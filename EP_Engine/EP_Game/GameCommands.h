#pragma once
#include "Command.h"

enum class Commands
{
	Fire = 0,
	Duck = 1,
	Fart = 2,
	Jump = 3,
	//...
};

class EmptyCommand : public Command /* For command vector creation only */
{
public:
	void Execute() override { std::cout << "NO COMMAND WAS ASSIGNED TO THIS BUTTON\n"; return; };
	virtual ~EmptyCommand() override = default;
};

class FireCommand : public Command
{
public:
	void Execute() override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fire);
		Logger::GetInstance().Log("Fire");
	};
	virtual ~FireCommand() override = default;
};

class DuckCommand : public Command
{
public:
	void Execute() override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Duck);
		Logger::GetInstance().Log("Duck");
	};

	~DuckCommand() override = default;
};

class JumpCommand : public Command
{
public:
	void Execute() override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Jump);

		Logger::GetInstance().Log("Jump");
	};
	~JumpCommand() override = default;
};

class FartCommand : public Command
{
public:
	void Execute() override
	{
		ServiceLocator::GetAudio().PlaySounds((int)Commands::Fart);
		Logger::GetInstance().Log("Fart");
	};
	~FartCommand() override = default;
};