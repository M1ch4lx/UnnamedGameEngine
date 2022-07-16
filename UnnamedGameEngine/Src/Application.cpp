#include "Pch.h"
#include "Application.h"

#include <iostream>
#include <string>

#include "Platform/GraphicsLibrary.h"
#include "Data/Image.h"

using namespace UEngine;

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

	/*auto printMat = [](const Matrix4& mat)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	};

	Matrix4 mat1;
	mat1[0][0] = 1.f;
	mat1[0][1] = 2.f;
	mat1[0][2] = 3.f;
	mat1[1][1] = 7.f;
	mat1[1][2] = 8.f;
	mat1[1][3] = 9.f;

	Matrix4 mat2;
	mat2[0][0] = 1.f;
	mat2[0][1] = 2.f;
	mat2[0][2] = 2.f;
	mat2[1][1] = 1.f;
	mat2[1][2] = 3.f;
	mat2[1][3] = 4.f;
	mat2[3][2] = 2.f;
	mat2[3][3] = 1.f;

	printMat(mat1);
	printMat(mat2);
	auto product = mat1 * mat2;
	printMat(product);*/

	auto printMat = [](const Matrix4& mat)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	};

	GraphicsLibrary::InitializeOpenGL();

	auto factory = GraphicsLibrary::Factory();
	
	auto window = factory->CreateWindow();
	
	window->Open({"Atron", 960, 540});

	auto renderer2D = factory->CreateRenderer2D(window->Context());

	GraphicsLibrary::InitializeImGui(window);

	auto context = window->Context();

	bool applicationRunning = true;

	window->ConnectSignal<WindowCloseSignal>([&](WindowCloseSignal& signal)
		{
			std::cout << "Closing window" << std::endl;
			applicationRunning = false;
		});

	window->ConnectSignal<WindowResizeSignal>([&](WindowResizeSignal& signal)
		{
			return;
		});

	auto flatColorShader = factory->CreateShader(
		ShaderSource("Assets/Shaders/BasicVertex.glsl"),
		ShaderSource("Assets/Shaders/FlatColor.glsl")
	);

	renderer2D->ShadersConfiguration().FlatColor = flatColorShader;

	Image image;
	image.LoadFromFile("Assets/Textures/test.png");

	
	// auto texture = factory->CreateTexture(image);
	// texture->Bind(0);
	// renderer2D->ShadersConfiguration().FlatColor->SetUniform("Texture", 0);

	Camera2D camera;

	Transformation2D model;
	model.Position = Vector(0.f, 0.f);
	model.Scale = Vector(1.f, 1.f);

	Timer timer;

	float cameraSize = camera.GetSize();

	auto renderImGui = [&]()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Quad options");

		ImGui::SliderFloat("rotation", &model.Rotation, 0.f, 360.f);

		ImGui::SliderFloat2("position", model.Position.Data(), -200.f, 200.f);

		ImGui::SliderFloat2("scale", model.Scale.Data(), 0.f, 10.f);

		ImGui::End();

		ImGui::Begin("Camera options");

		ImGui::SliderFloat("rotation", &camera.GetTransformation().Rotation, 0.f, 360.f);

		ImGui::SliderFloat2("position", camera.GetTransformation().Position.Data(), -200.f, 200.f);

		ImGui::SliderFloat("size", &cameraSize, 0.f, 10.f);

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	};

	while (applicationRunning)
	{
		camera.SetSize(cameraSize);

		renderer2D->ClearScreen();

		renderer2D->BeginScene(camera);

		// Render scene
		renderer2D->RenderRectangle(model, Color4(1.f, 1.f, 1.f, 1.f));

		// Render GUI
		//glClear(GL_DEPTH_BUFFER_BIT);
		renderImGui();

		renderer2D->EndScene();

		renderer2D->Display();

		window->ProcessEvents();

		timer.Wait(16);
	}

	GraphicsLibrary::TerminateImGui();

	window->Destroy();

	GraphicsLibrary::TerminateOpenGL();
}