#pragma once
#include "Singleton.h"

namespace ep
{
	class ApplicationManager : Singleton<ApplicationManager>
	{
	public:
		ApplicationManager();
		~ApplicationManager();
		ApplicationManager(const ApplicationManager& other) = delete;
		ApplicationManager(ApplicationManager&& other) = delete;
		ApplicationManager& operator=(const ApplicationManager& other) = delete;
		ApplicationManager& operator=(ApplicationManager&& other) = delete;

	private:

	};
}

