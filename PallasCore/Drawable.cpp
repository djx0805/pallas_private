#include "Drawable.h"
#include "RenderStage.h"
namespace pallas
{
	void Drawable::Cull(RenderStage* renderStage) {
		renderStage->GetRenderQueue()->AddRenderData(this, new RefMatrix(*renderStage->GetModelMatrix()), renderStage->GetCurrentMaterial(), 0);
	}
}