#include "Pch.h"
#include "Application.h"

#include <iostream>
#include <string>

#include "Components/Transform.h"
#include "Components/TransformSystem.h"
#include "Core/Container.h"
#include "Core/Signal.h"
#include "Core/Timer.h"
#include "Core/Entity.h"

#include "Platform/Graphics.h"

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

	Graphics::InitializeOpenGL();

	auto factory = Graphics::Factory();
	
	auto window = factory->CreateWindow();
	auto renderer = factory->CreateRenderer2D(window->Context());

	window->Open({"Atron", 960, 540});

	Graphics::InitializeImGui(window);

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

	auto shader = factory->CreateShader(
		ShaderSource("Assets/Shaders/VertexShader.glsl"),
		ShaderSource("Assets/Shaders/FragmentShader.glsl")
	);

	Vertex vertices[] = {
		Vertex(50.f,  50.f, 0.0f),   // top right
		Vertex(50.f, -50.f, 0.0f),   // bottom right
		Vertex(-50.f, -50.f, 0.0f),  // bottom left
		Vertex(-50.f,  50.f, 0.0f)   // top left 
	};

	const auto& layout = Vertex::Layout();

	auto vbo = factory->CreateVertexBuffer();
	vbo->SetData(vertices, 4, layout);

	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	auto ibo = factory->CreateIndexBuffer(indices, 6);

	auto vao = factory->CreateVertexArray(vbo, ibo);
	
	shader->Bind();
	vao->Bind();

	Camera2D camera;
	renderer->SetCamera(camera);

	printMat(renderer->GetViewMatrix());
	printMat(renderer->GetProjectionMatrix());

	auto cSize = camera.CalculateSize();
	std::cout << cSize.x << " " << cSize.y << std::endl;

	Transformation model;
	model.position = Vector2(0.f, 0.f);
	model.scale = Vector2(1.f, 1.f);
	model.rotation = 30.f;

	auto modelMatrix = model.ToMatrix();

	std::cout << "Model matrix" << std::endl;
	printMat(modelMatrix);

	shader->SetMatrix4("model", modelMatrix);
	shader->SetMatrix4("view", renderer->GetViewMatrix());
	shader->SetMatrix4("projection", renderer->GetProjectionMatrix());

	Timer timer;

	Vector4 color;

	while (applicationRunning)
	{
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Create a window called "My First Tool", with a menu bar.
		ImGui::Begin("My First Tool");
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) {  }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Edit a color (stored as ~4 floats)
		ImGui::ColorEdit4("Color", (float*)&color);

		// Plot some values
		const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
		ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		// Display contents in a scrolling region
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
		ImGui::BeginChild("Scrolling");
		for (int n = 0; n < 50; n++)
			ImGui::Text("%04d: Some text", n);
		ImGui::EndChild();
		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		context->SwapBuffers();

		window->ProcessEvents();

		timer.Wait(16);
	}

	Graphics::TerminateImGui();

	window->Destroy();

	Graphics::TerminateOpenGL();
}