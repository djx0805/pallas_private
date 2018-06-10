#pragma once
#include "Event.h"

namespace pallas
{
	class CameraManipulator : public GUIEventHandler
	{
	public:
		CameraManipulator() {}
		virtual ~CameraManipulator() {}
		virtual bool Handle(Event* pevent) = 0;
	};
}