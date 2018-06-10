#include "SceneGraphNode.h"
#include "Group.h"
#include "RenderStage.h"

namespace pallas
{
		void SceneGraphNode::AddUpdateCallBack(UpdateCallBack* updateCallBack) {
			if (mUpdateGraphNode == nullptr) {
				mUpdateGraphNode = pallas::ref_ptr<UpdateGraphNode>(new UpdateGraphNode());
				mountUpdateGraphNode();
			}
			//
			mUpdateGraphNode->AddUpdateCallBack(updateCallBack);
		}

		void SceneGraphNode::RemoveUpdateCallBack(UpdateCallBack* updateCallBack) {
			if (mUpdateGraphNode == nullptr)
				return;
			//
			mUpdateGraphNode->RemoveUpdateCallBack(updateCallBack);
		}

		int SceneGraphNode::GetNumUpdateCallBak()
		{
			if (mUpdateGraphNode != nullptr)
				return mUpdateGraphNode->GetNumUpdateCallBack();
			else
				return 0;
		}

		SceneGraphNode::UpdateCallBack* SceneGraphNode::GetUpdateCallBack(int index)
		{
			if (mUpdateGraphNode != nullptr)
				return mUpdateGraphNode->GetUpdateCallBack(index);
			else
				return nullptr;
		}

		void SceneGraphNode::mountUpdateGraphNode() {
			if (mUpdateGraphNode == nullptr)
				return;
			//
			for (auto itr : mParents) {
				if(itr->mUpdateGraphNode == nullptr)
					itr->mUpdateGraphNode = pallas::ref_ptr<UpdateGraphNode>(new UpdateGraphNode());
				//
				if (!itr->mUpdateGraphNode->ContainsNode(mUpdateGraphNode.get())) {
					itr->mUpdateGraphNode->AddChild(mUpdateGraphNode.get());
					itr->mountUpdateGraphNode();
				}
			}
		}

		void SceneGraphNode::unMountUpdateGraphNode() {
			if (mUpdateGraphNode->GetNumChildren() > 0)
				return;
			//
			for (auto itr : mParents) {
				if (itr->mUpdateGraphNode->ContainsNode(mUpdateGraphNode.get())) {
					itr->unMountUpdateGraphNode();
					itr->mUpdateGraphNode->RemoveChild(mUpdateGraphNode.get());
				}
			}
			mUpdateGraphNode = nullptr;
		}

		void SceneGraphNode::Update() {
			if (mUpdateGraphNode == nullptr)
				return;
			//
			mUpdateGraphNode->Update();
		}


		BoundingSphere SceneGraphNode::GetBoundingSphere() {
			return BoundingSphere();
		}

		BoundingBox SceneGraphNode::GetBoundingBox() {
			return BoundingBox();
		}

		void SceneGraphNode::Cull(RenderStage* renderStage) {
			if (!renderStage->CheckVisible(this))
				return;
			//
			renderStage->PushModelMatrix(GetTransform()->GetTransformMatrix());
			if (GetMaterial() != nullptr)
				renderStage->PushMaterial(GetMaterial());
			//do something
			
			//
			if (GetMaterial() != nullptr)
				renderStage->PopMaterial();
			renderStage->PopModelMatrix();
		}
}