#include "Group.h"
#include "RenderStage.h"

namespace pallas
{
	void Group::Cull(RenderStage* renderStage) {
		for (auto itr_child : mChildren) {
			renderStage->Cull(itr_child.get());
		}
	}
}