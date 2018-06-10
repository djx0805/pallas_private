#pragma once
#include "SceneGraphNode.h"
#include <mutex>
#include <thread>
#include <unordered_map>
#include "RenderTarget.h"
#include "..\PallasMath\Mat4.h"
#include "CameraManipulator.h"

namespace pallas
{
	class Scene;
	class PALLASCORE_API Camera : public SceneNode
	{
	public:
		Camera() {}
		virtual ~Camera() {}
		virtual void AddCullingNode(pallas::ref_ptr<SceneGraphNode>& SceneGraphNode);
		virtual void GetCullingNodes(std::vector<SceneGraphNode*>& SceneGraphNodes);

		virtual void BindRenderTarget(RenderTarget* prenderTarget);
		virtual RenderTarget* GetRenderTarget();

		virtual void AddManipulator(CameraManipulator* pmanipulator);
		virtual void RemoveManipulator(CameraManipulator* pmanipulator);
		virtual int GetNumManipulator();
		virtual CameraManipulator* GetManipulator(int index);

		virtual void SetViewMatrix(const Mat4d& viewMatrix) { mViewMatrix = viewMatrix; }
		virtual Mat4d GetViewMatrix() { return mViewMatrix; }
		virtual void SetProjectionMatrix(const Mat4d& projectionMatrix) { mProjectionMatrix = projectionMatrix; }
		virtual Mat4d GetProjectionMatrix() { return mProjectionMatrix; }

		virtual void SetRenderOrder(int order) {
			mRenderOrder = order;
		}
		virtual int GetRenderOrder() {
			return mRenderOrder;
		}

		virtual void Cull(Scene* pscene);
	protected:
		std::mutex mMutexUpdate;
		std::vector<pallas::ref_ptr<SceneGraphNode>> mCullingNodes;
        //
        ref_ptr<RenderTarget> mRenderTarget;
		std::vector<ref_ptr<CameraManipulator>> mManipulators;
		//
		Mat4d mViewMatrix;
		Mat4d mProjectionMatrix;
		//
		int mRenderOrder = 0;
	};
}
