#pragma once
#include <stack>
#include <unordered_map>
#include "Object.h"
#include "Drawable.h"
#include "Matrix.h"
#include "Material.h"
#include "RenderTarget.h"
#include "RenderQueue.h"

namespace pallas
{
	class Scene;
	class PALLASCORE_API RenderStage : public Object
	{
	public:
		RenderStage() {
			mModelMatrixStack.push(Matrix());
			mRenderQueue = new RenderQueue();
		}
		virtual ~RenderStage() {}
		//
		void SetScene(Scene* powner) {
			mOwner = powner;
		}

		Scene* GetScene() {
			return mOwner;
		}

		Matrix* GetViewMatrix() {
			return &mViewMatrix;
		}
		void SetViewMatrix(const Matrix& mt) {
			mViewMatrix = mt;
		}

		Matrix* GetProjectionMatrix() {
			return &mProjectionMatrix;
		}
		void SetProjectionMatrix(const Matrix& mt) {
			mProjectionMatrix = mt;
		}

		Matrix* GetModelMatrix() {
			return &mModelMatrixStack.top();
		}

		void SetRenderTarget(RenderTarget* rt) {
			mRenderTarget = rt;
		}

		RenderTarget* GetRenderTarget() {
			return mRenderTarget.get();
		}
		
		void SetRenderOrder(int order) {
			mRenderOrder = order;
		}

		int GerRenderOrder() {
			return mRenderOrder;
		}

		void  PushModelMatrix(const Matrix& mt) {
			mModelMatrixStack.push(mModelMatrixStack.top()*mt);
		}

		void PopModelMatrix() {
			mModelMatrixStack.pop();
		}

		void PushMaterial(Material* m) {
			mMaterialStack.push(combineMaterial(mMaterialStack.top().get(), m));
		}

		void PopMaterial() {
			mMaterialStack.pop();
		}

		Material* GetCurrentMaterial() {
			return mMaterialStack.top().get();
		}

		RenderQueue* GetRenderQueue() {
			return mRenderQueue.get();
		}

		virtual bool CheckVisible(SceneGraphNode* pnode);
		virtual void Cull(SceneGraphNode* pnode);

	protected:
		Material* combineMaterial(Material* m_a, Material* m_b) {
			return new Material();
		}
	protected:
		std::stack<Matrix> mModelMatrixStack;
		pallas::ref_ptr<RenderTarget> mRenderTarget;
		Matrix mViewMatrix;
		Matrix mProjectionMatrix;
		Scene* mOwner = nullptr;
		std::stack<pallas::ref_ptr<Material>> mMaterialStack;
		int mRenderOrder;
		pallas::ref_ptr<RenderQueue> mRenderQueue;
	};
}