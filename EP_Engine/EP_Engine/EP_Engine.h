#pragma once
struct SDL_Window;

class FontComponent;

namespace ep
{
	class EP_Engine
	{
	public:
		~EP_Engine();
		void Initialize();
		void LoadGame();
		void CleanUp();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		FontComponent* m_pFpsFont;
	};
}

