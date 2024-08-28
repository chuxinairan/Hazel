#pragma once
#include "hzpch.h"
#include "Hazel/core.h"

namespace Hazel
{
	enum class EventType 
	{
		None = 0,
		WindowClose, WindowResize, WindowsFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,
	};

	enum  EventCatagory
	{
		EventCatagoryApplication = BIT(0),
		EventCatagoryInput =	   BIT(1),
		EventCatagoryKeyboard =    BIT(2),
		EventCatagoryMouse =       BIT(3),
		EventCatagoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }; \
								virtual EventType GetEventType() const override { return GetStaticType(); }; \
								virtual const char* GetName() const override { return #type; };

#define EVENT_CLASS_CATAGORY(catagory) virtual int GetCatagoryFlags() const override { return catagory; };

	class Event
	{
		friend class EventDispatcher;
	public:
		bool m_handle;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCatagoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCatagory(EventCatagory catagory)
		{
			return GetCatagoryFlags() & catagory;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_handle = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& event) 
	{
		os << event.ToString();
		return os;
	}
}