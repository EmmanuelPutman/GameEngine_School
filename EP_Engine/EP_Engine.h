#pragma once
struct SDL_Window;

class FontComponent;
#include <memory>

namespace ep
{
	class EP_Engine
	{
	public:
		void Initialize();
		void LoadGame();
		void CleanUp();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		std::shared_ptr<FontComponent> m_pFpsFont;
	};
}

