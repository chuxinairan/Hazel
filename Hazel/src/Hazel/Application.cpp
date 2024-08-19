#include "hzpch.h"
#include "Application.h"
#include "Hazel/Events/Application.h"
#include "Hazel/Log.h"

namespace Hazel {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowsResizeEvent e(1280, 720);
		HZ_CORE_TRACE(e);
		while (true);
	}
}