#include "RenderStage.h"
#include "Mesh.h"

namespace pallas
{
	bool RenderStage::CheckVisible(SceneGraphNode* pnode)
	{
		return true;
	}

	void RenderStage::Cull(SceneGraphNode* pnode)
	{
		if (!CheckVisible(pnode))
			return;
		//
		bool hasMaterial = false;
		PushModelMatrix(pnode->GetTransform()->GetTransformMatrix());
		if (pnode->GetMaterial() != nullptr) {
			PushMaterial(pnode->GetMaterial());
			hasMaterial = true;
		}
		//
		pnode->Cull(this);
		//
		if (hasMaterial)
			PopMaterial();
		PopModelMatrix();
	}
}