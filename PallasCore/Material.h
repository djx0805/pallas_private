#pragma once
#include "SceneNode.h"
#include "RenderSetting.h"
#include "RenderPass.h"
#include <vector>

namespace pallas
{
	class Material : public SceneNode::Attribute
	{
	public:
		Material() {
			mName = "material";
		}
		~Material() {}
		//
		RenderSetting* GetOrCreateRenderSetting() {
			if (mRenderSetting == nullptr)
				mRenderSetting = new RenderSetting();
			//
			return mRenderSetting.get();
		}

		RenderSetting* GetRenderSetting() {
			return mRenderSetting.get();
		}

		void SetRenderSetting(RenderSetting* renderSetting) {
			mRenderSetting = renderSetting;
		}
		//
		int GetNumRenderPass() {
			return mRenderPass.size();
		}

		int AddRenderPass(RenderPass* renderPass) {
			mRenderPass.push_back(renderPass);
		}

		void RemoveRenderPass(RenderPass* renderPass) {
			for (auto itr = mRenderPass.begin(); itr != mRenderPass.end(); ++itr) {
				if (itr->get() == renderPass) {
					mRenderPass.erase(itr);
					return;
				}
			}
		}
	private:
		pallas::ref_ptr<RenderSetting> mRenderSetting;
		std::vector<pallas::ref_ptr<RenderPass>>mRenderPass;
	};
}