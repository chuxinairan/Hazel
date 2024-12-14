#include "hazel.h"
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel
{
	class HazelEditor : public Application
	{
	public:
		HazelEditor()
		{
			PushOverlay(new EditorLayer());
			//PushOverlay(new ExampleLayer());
		}
		~HazelEditor() {}
	};

	Application* CreateApplication()
	{
		return new HazelEditor();
	};
}
