#include "EP_Engine_PCH.h"
#include "EP_Engine.h"

#include <chrono>
#include <thread>
#include <SDL.h>

#include "Renderer.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "../EP_Game/BubbleBobble_Game.h"

#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "FontComponent.h"
#include "FpsComponent.h"


using namespace std;
using namespace std::chrono;

ep::EP_Engine::~EP_Engine()
{
	SafeDelete(m_Game);
}

void ep::EP_Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	
	m_Window = SDL_CreateWindow(
		"EP_Game",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	
	Renderer::GetInstance().Init(m_Window);

	m_GameTime = GameTime();
	m_GameTime.WindowWidth = 640;
	m_GameTime.WindowHeight = 480;
}

void ep::EP_Engine::LoadGame()
{
	/*
	auto scene = SceneManager::GetInstance().CreateScene("Test");
	GameObject* gameObject = new GameObject();
	//Transformcomponent
	TransformComponent* transform = new TransformComponent();
	transform->ChangePositionTo(0.f, 0.f, 0.f);
	gameObject->AddComponent(transform);
	//RenderComponent
	RenderComponent* render = new RenderComponent();
	render->SetTexture("background.jpg");
	render->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(render);
	//GameObject
	scene->Add(gameObject);
	

	gameObject = new GameObject();
	//TransformComponent 2nd image
	transform = new TransformComponent();
	transform->ChangePositionTo(216.f, 180.f, 0.f);
	gameObject->AddComponent(transform);
	//RenderComponent 2nd image
	render = new RenderComponent();
	render->SetTexture("logo.png");
	render->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(render);
	//adding a 2nd gameobject
	scene->Add(gameObject);


	gameObject = new GameObject();
	//TransformComponent text1
	transform = new TransformComponent();
	transform->ChangePositionTo(80.f, 20.f, 0.f);
	gameObject->AddComponent(transform);
	//FontComponent text1
	FontComponent* font = new FontComponent("Lingua.otf", 36, "Programming 4 assignment");
	//font->SetFont("Lingua.otf", 36);
	//font->SetText("Programming 4 assignment");
	font->SetColor(255.f, 255.f, 255.f, 255.f);
	font->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(font);
	//GameObject adding text1
	scene->Add(gameObject);

	gameObject = new GameObject();
	//TransformComponent text1
	transform = new TransformComponent();
	transform->ChangePositionTo(0.f, 0.f, 0.f);
	gameObject->AddComponent(transform);
	//FontComponent text1
	FpsComponent* fpsComponent = new FpsComponent("Lingua.otf", 26, "00");
	gameObject->AddComponent(fpsComponent);

	//GameObject adding text1
	scene->Add(gameObject);
	*/

	m_Game = new BubbleBobble_Game(m_GameTime);
}

void ep::EP_Engine::CleanUp()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void ep::EP_Engine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Resources/");

	LoadGame(); 

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto previousTime = high_resolution_clock::now();
		float timeBehind{ 0.f };

		int maxSkipFrames{ 2 }; // 60fps / 2 = 30fps (The min. I want to run my engine at)
		while (doContinue)
		{
			int nrOfFrames{};
			const auto currentTime = high_resolution_clock::now();
			float elapsed = duration<float>(currentTime - previousTime).count();
			
			previousTime = currentTime;
			timeBehind += elapsed;

			doContinue = input.ProcessInput();

			m_GameTime.elapsedSec = elapsed;

			while (timeBehind < MsPerFrame && nrOfFrames < maxSkipFrames)
			{
				++nrOfFrames;
				m_GameTime.FPS = int(nrOfFrames / elapsed);
				sceneManager.Update(m_GameTime);

				input.HandleInput(m_GameTime);

				m_Game->Update(m_GameTime);

				timeBehind -= MsPerFrame;
			}

			renderer.Render(m_GameTime);

		}
	}

	CleanUp();
}