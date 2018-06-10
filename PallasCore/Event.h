#pragma once
#include "Object.h"
namespace pallas
{
    class Event : public Referenced
    {
    public:
        Event() {}
        virtual ~Event() {}
    };

    class MouseEvent : public Event
    {
    public:
        MouseEvent() {}
        virtual ~MouseEvent() {}
    };

    class KeyBoardEvent : public Event
    {
    public:
        KeyBoardEvent() {}
        virtual ~KeyBoardEvent() {}
    };

	class EventHandler : public Object
	{
	public:
		EventHandler() {}
		virtual ~EventHandler() {}
		virtual bool Handle(Event* pevent) = 0;
	};

	class GUIEventHandler : public EventHandler
	{
	public:
		GUIEventHandler() {}
		virtual ~GUIEventHandler() {}
		virtual bool Handle(Event* pevent) = 0;
	};
}