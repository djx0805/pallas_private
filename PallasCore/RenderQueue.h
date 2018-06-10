#pragma once
#include <vector>
#include <unordered_map>
#include "Material.h"
#include "Drawable.h"
#include "Matrix.h"


namespace pallas
{
	class RenderQueue : public Referenced
	{
	public:
		struct RenderData
		{
			pallas::ref_ptr<Drawable> mDrawable = nullptr;
			RefMatrix* mModelMatrix = nullptr;
			Material* mMaterial;
			float mDepth = FLT_MAX;
		};
	public:
		RenderQueue() {}
		virtual ~RenderQueue() {}
		//
		void AddRenderData(Drawable* pnode, RefMatrix* modelMatrix, Material* material, float depth) {
			RenderData tmp;
			tmp.mDepth = depth;
			tmp.mDrawable = pnode;
			//
			auto itr_material = mMaterials.find((long long)material);
			if (itr_material == mMaterials.end()) {
				mMaterials[(long long)material] = material;
			}
			tmp.mMaterial = material;
			//
			auto itr_matrix = mModelMatrixes.find((long long)modelMatrix);
			if (itr_matrix == mModelMatrixes.end()) {
				mModelMatrixes[(long long)modelMatrix] = modelMatrix;
			}
			tmp.mModelMatrix = modelMatrix;
			//
			mRenderDatas.push_back(tmp);
		}
		void Sort() {

		}

		int GetNumRenderData() {
			return mRenderDatas.size();
		}

		RenderData* GetRenderData(int index) {
			return &mRenderDatas[index];
		}
	private:
		std::vector<RenderData> mRenderDatas;
		std::unordered_map<long long, pallas::ref_ptr<Material>> mMaterials;
		std::unordered_map<long long, pallas::ref_ptr<RefMatrix>> mModelMatrixes;
	};
}
