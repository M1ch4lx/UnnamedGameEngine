#include "Pch.h"
#include "Application.h"

#include <iostream>
#include <string>

#include "Components/Transform.h"
#include "Components/TransformSystem.h"
#include "Core/Container.h"
#include "Core/Factory.h"
#include "Core/Signal.h"

#include "Platform/RenderingAPI.h"

using namespace Atron;

template<class T>
void Print(const std::string& text, const T& var)
{
	std::cout << text << var << std::endl;
}

void Application::Run(int argc, char* argv[])
{
	/*Service<EntitiesService> entitiesService;
	Service<ComponentsService> componentsService;

	System<TransformSystem> transformSystem;

	Entity* root = entitiesService->CreateEntity();

	Entity* gen1a = entitiesService->CreateEntity();
	Entity* gen1b = entitiesService->CreateEntity();
	root->AddChild(gen1a);
	root->AddChild(gen1b);

	Entity* gen2a = entitiesService->CreateEntity();
	Entity* gen2b = entitiesService->CreateEntity();
	gen1a->AddChild(gen2a);
	gen1a->AddChild(gen2b);

	gen2a->AddComponent<Transform>();
	Transform* transform = gen2a->GetComponent<Transform>();

	transformSystem->Update();

	entitiesService->UpdateEntities();
	componentsService->UpdateComponents();

	transform = gen2a->GetComponent<Transform>();

	gen2a->RemoveComponent<Transform>();

	entitiesService->UpdateEntities();
	componentsService->UpdateComponents();

	transformSystem->Update();*/

	RenderingAPI::InitializeOpenGL();

	Fabricate<Window> window;
	Fabricate<Renderer2D> renderer;

	window->Open({"Atron", 800, 600});

	auto context = window->GetContext();

	context->Bind();

	window->ConnectSignal<WindowCloseSignal>([&](WindowCloseSignal& signal)
		{
			std::cout << "Closing window" << std::endl;
			window->Destroy();
		});

	window->ConnectSignal<WindowResizeSignal>([&](WindowResizeSignal& signal)
		{
			std::cout << signal.Width() << " " << signal.Height() << std::endl;
		});

	while (window->IsOpen())
	{
		context->SwapBuffers();

		window->ProcessEvents();
	}

	RenderingAPI::TerminateOpenGL();

	int i = 0;
}