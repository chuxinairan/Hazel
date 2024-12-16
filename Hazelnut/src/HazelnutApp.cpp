#include "hazel.h"
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel
{
	class Hazelnut : public Application
	{
	public:
		Hazelnut()
		{
			PushOverlay(new EditorLayer());
			//PushOverlay(new ExampleLayer());
		}
		~Hazelnut() {}
	};

	Application* CreateApplication()
	{
		return new Hazelnut();
	};
}
