#pragma once
#include "Event.h"

namespace Hazel
{
	class WindowsCloseEvent : public Event
	{
	public:
		WindowsCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowsClose)
		EVENT_CLASS_CATAGORY(EventCatagoryApplication)
	};

	class WindowsResizeEvent : public Event
	{
	public:
		WindowsResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height)
		{
		}

		inline int GetWidth() const { return m_Width; };
		inline int GetHeight() const { return m_Height; };

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowsResize)
		EVENT_CLASS_CATAGORY(EventCatagoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATAGORY(EventCatagoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATAGORY(EventCatagoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATAGORY(EventCatagoryApplication)
	};
}