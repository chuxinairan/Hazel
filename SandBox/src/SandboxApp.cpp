#include "hazel.h"

#include <Hazel/Core/EntryPoint.h>

#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Sandbox2D());
		//PushOverlay(new ExampleLayer());
	}
	~Sandbox(){}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
};