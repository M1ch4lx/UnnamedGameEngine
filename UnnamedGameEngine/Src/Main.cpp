#include "Pch.h"
#include "Application.h"

int main(int argc, char* argv[])
{
	Application* application = new Application();

	application->Run(argc, argv);

	delete application;

	return 0;
}