#pragma once
#include "Object.h"
namespace pallas
{
	class RenderWindow;
	class FrameBuffer;
    class RenderTarget : public Object
    {
    public:
        RenderTarget() {}
        virtual ~RenderTarget() {}
		virtual RenderWindow* asRenderWindow() { 
			return nullptr;
		};
		virtual FrameBuffer* asFrameBuffer() {
			return nullptr;
		};
    };
}