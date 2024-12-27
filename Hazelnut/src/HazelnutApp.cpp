#include "hazel.h"

#include "EditorLayer.h"

#include "Hazel/Core/EntryPoint.h"

namespace Hazel
{
	class Hazelnut : public Application
	{
	public:
		Hazelnut(ApplicationCommandLineArgs args)
			: Application("Hazelnut", args)
		{
			PushLayer(new EditorLayer());
		}
		~Hazelnut() {}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new Hazelnut(args);
	}
}
