#pragma once
#include "RenderTarget.h"
namespace pallas
{
    class FrameBuffer : public RenderTarget
    {
    public:
        FrameBuffer() {}
        virtual ~FrameBuffer() {}
        //
		virtual FrameBuffer* asFrameBuffer() {
			return this;
		}
    };
}