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

#include "TransformComponent.h"
#include "RenderComponent.h"
#include "FontComponent.h"

using namespace std;
using namespace std::chrono;

void ep::EP_Engine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"EP_Engine",
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
}

void ep::EP_Engine::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Test");

	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
	//Transformcomponent
	std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>();
	transform->ChangePositionTo(0.f, 0.f, 0.f);
	gameObject->AddComponent(transform);
	//RenderComponent
	std::shared_ptr<RenderComponent> render = std::make_shared<RenderComponent>();
	render->SetTexture("background.jpg");
	render->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(render);
	//GameObject
	scene.Add(gameObject);
	

	gameObject = std::make_shared<GameObject>();
	//TransformComponent 2nd image
	transform = std::make_shared<TransformComponent>();
	transform->ChangePositionTo(216.f, 180.f, 0.f);
	gameObject->AddComponent(transform);
	//RenderComponent 2nd image
	render = std::make_shared<RenderComponent>();
	render->SetTexture("logo.png");
	render->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(render);
	//adding a 2nd gameobject
	scene.Add(gameObject);


	gameObject = std::make_shared<GameObject>();
	//TransformComponent text1
	transform = std::make_shared<TransformComponent>();
	transform->ChangePositionTo(80.f, 20.f, 0.f);
	gameObject->AddComponent(transform);
	//FontComponent text1
	std::shared_ptr<FontComponent> font = std::make_shared<FontComponent>("Lingua.otf", 36, "Programming 4 assignment");
	//font->SetFont("Lingua.otf", 36);
	//font->SetText("Programming 4 assignment");
	font->SetColor(255.f, 255.f, 255.f, 255.f);
	font->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(font);
	//GameObject adding text1
	scene.Add(gameObject);

	gameObject = std::make_shared<GameObject>();
	//TransformComponent text1
	transform = std::make_shared<TransformComponent>();
	transform->ChangePositionTo(0.f, 0.f, 0.f);
	gameObject->AddComponent(transform);
	//FontComponent text1
	m_pFpsFont = std::make_shared<FontComponent>("Lingua.otf", 22, "00 FPS");
	//font->SetFont("Lingua.otf", 36);
	//font->SetText("00 FPS");
	m_pFpsFont->SetColor(255.f, 255.f, 0.f, 255.f);
	m_pFpsFont->SetPosition(transform->GetPosition().x, transform->GetPosition().y);
	gameObject->AddComponent(m_pFpsFont);
	//GameObject adding text1
	scene.Add(gameObject);
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
		float timeBehind{};
		while (doContinue)
		{
			int nrOfFrames{};
			const auto currentTime = high_resolution_clock::now();
			float elapsed = duration<float>(currentTime - previousTime).count();
			previousTime = currentTime;
			timeBehind += elapsed;

			doContinue = input.ProcessInput();


			while (timeBehind >= MsPerFrame)
			{
				++nrOfFrames;
				sceneManager.Update();
				m_pFpsFont->SetText(std::to_string(int(nrOfFrames / elapsed)) + " FPS");

				timeBehind -= MsPerFrame;
			}

			renderer.Render();

		}
	}

	CleanUp();
}