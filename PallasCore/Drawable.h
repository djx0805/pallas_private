#pragma once
#include "SceneGraphNode.h"

namespace pallas
{
	class VertexData;
    class PALLASCORE_API Drawable : public SceneGraphNode
    {
    public:
        Drawable(){}
        virtual ~Drawable() {}
		//
		virtual void Cull(RenderStage* renderStage) override;
		//
		virtual VertexData* GetOrBuildVertexData() { return nullptr; }
    };
}