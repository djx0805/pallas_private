#pragma once
#include"Object.h"
#include "RenderSetting.h"
#include "GPUProgram.h"

namespace pallas
{
	class RenderPass : public Object
	{
	public:
		RenderPass() {}
		virtual ~RenderPass() {}
		//
		virtual RenderSetting* GetRenderSetting() {
			return mRenderSetting.get();
		}

		virtual RenderSetting* GetOrCreateRenderSetting() {
			if (mRenderSetting == nullptr)
				mRenderSetting = new RenderSetting();
			//
			return mRenderSetting.get();
		}

		virtual void SetRenderSetting(RenderSetting* renderSetting) {
			mRenderSetting = renderSetting;
		}
		//
		virtual GPUProgram* GetVertexProgram() {
			return mVertexProgram.get();
		}
		virtual void SetVertexProgram(GPUProgram* p) {
			mVertexProgram = p;
		}

		virtual GPUProgram* GetFragmentProgram() {
			return mFramgentProgram.get();
		}
		virtual void SetFragmentProgram(GPUProgram* p) {
			mFramgentProgram = p;
		}
	protected:
		pallas::ref_ptr<RenderSetting> mRenderSetting;
		pallas::ref_ptr<GPUProgram> mVertexProgram;
		pallas::ref_ptr<GPUProgram> mFramgentProgram;
	};
}