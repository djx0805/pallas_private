#include "Camera.h"
#include "Scene.h"
#include "RenderWindow.h"

namespace pallas
{
	void Camera::AddCullingNode(pallas::ref_ptr<SceneGraphNode>& SceneGraphNode) {
		std::lock_guard<std::mutex> lock(mMutexUpdate);
		mCullingNodes.push_back(SceneGraphNode);
	}
	void Camera::GetCullingNodes(std::vector<SceneGraphNode*>& SceneGraphNodes) {
		std::lock_guard<std::mutex> lock(mMutexUpdate);
		for (auto itr : mCullingNodes) {
			if ((itr->GetState() & SceneGraphNode::State::NST_UNVISIBLE) != 0)
				continue;
			//
			SceneGraphNodes.push_back(itr.get());
		}
	}

	void Camera::BindRenderTarget(RenderTarget* prenderTarget) {
		mRenderTarget = prenderTarget;
		//
		if (mRenderTarget != nullptr && mRenderTarget->asRenderWindow() != nullptr) {
			for (auto itr : mManipulators) {
				mRenderTarget->asRenderWindow()->AddWindowEventHander(itr.get());
			}
		}
	}

	RenderTarget* Camera::GetRenderTarget() {
		return mRenderTarget.get();
	}

	void Camera::AddManipulator(CameraManipulator* pmanipulator) {
		mManipulators.push_back(pmanipulator);
		//
		if (mRenderTarget != nullptr && mRenderTarget->asRenderWindow() != nullptr) {
			mRenderTarget->asRenderWindow()->AddWindowEventHander(pmanipulator);
		}
	}
	void Camera::RemoveManipulator(CameraManipulator* pmanipulator) {
		for (auto itr = mManipulators.begin(); itr != mManipulators.end(); ++itr) {
			if (itr->get()->GetID() == pmanipulator->GetID()) {
				mManipulators.erase(itr);
				break;
			}
		}
		//
		if (mRenderTarget != nullptr && mRenderTarget->asRenderWindow() != nullptr) {
			mRenderTarget->asRenderWindow()->RemoveWindowEventHandler(pmanipulator);
		}
	}

	int Camera::GetNumManipulator() {
		return mManipulators.size();
	}

	CameraManipulator* Camera::GetManipulator(int index) {
		return mManipulators[index].get();
	}

	void Camera::Cull(Scene* pscene) {
		auto renderStage = new RenderStage();
		renderStage->SetScene(pscene);
		renderStage->SetViewMatrix(mViewMatrix);
		renderStage->SetProjectionMatrix(mProjectionMatrix);
		renderStage->SetRenderTarget(mRenderTarget);
		renderStage->SetRenderOrder(mRenderOrder);
		//
		if (mCullingNodes.size() > 0) {
			for (auto itr : mCullingNodes) 
				itr->Cull(renderStage);
		}
		else {
			for (int i = 0; i < pscene->GetNumSceneGraphNode(); ++i)
				pscene->GetSceneGraphNode(i)->Cull(renderStage);
		}
		//
		pscene->addRenderStage(renderStage);
	}
}