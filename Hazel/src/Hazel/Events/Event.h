#pragma once
#include "hzpch.h"
#include "Hazel/Core/core.h"

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

	enum  EventCategory
	{
		EventCategoryApplication = BIT(0),
		EventCategoryInput =	   BIT(1),
		EventCategoryKeyboard =    BIT(2),
		EventCategoryMouse =       BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }; \
								virtual EventType GetEventType() const override { return GetStaticType(); }; \
								virtual const char* GetName() const override { return #type; };

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; };

	class Event
	{
		friend class EventDispatcher;
	public:
		bool m_handle = false;;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
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