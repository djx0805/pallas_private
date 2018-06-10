#pragma once
#include "Object.h"
#include "RenderStage.h"

namespace pallas
{
	class Renderer : public Object
	{
	public:
		Renderer() {}
		virtual ~Renderer() {}
		//
		virtual void Render(RenderStage* prs) {}
	};
}
