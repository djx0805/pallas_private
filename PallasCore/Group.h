#pragma once
#include "SceneGraphNode.h"
#include <vector>

namespace pallas
{
	class PALLASCORE_API Group : public SceneGraphNode
	{
	public:
		Group() {}

        virtual void AddChild(SceneGraphNode* child) {
            mChildren.push_back(child);
			child->addParent(this);
        }

		virtual void RemoveChild(SceneGraphNode* child) {
			for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
				if (itr->get() == child) {
					if (mUpdateGraphNode != nullptr) {
						mUpdateGraphNode->RemoveChild(child->mUpdateGraphNode.get());
						unMountUpdateGraphNode();
					}
					(*itr)->removeParent(this);
					mChildren.erase(itr);
					break;
				}
			}
		}

		virtual int GetNumChildren() {
			return mChildren.size();
		}

		virtual SceneGraphNode* GetChild(int index) {
			return mChildren[index].get();
		}

		virtual bool IsEntirety() {
			return mAsEntirety;
		}

		virtual void AsEntirety(bool as_entirety) {
			mAsEntirety = as_entirety;
		}

		virtual void Cull(RenderStage* renderStage) override;
		//
    protected:
        std::vector<pallas::ref_ptr<SceneGraphNode>> mChildren;
		bool mAsEntirety = false;
	protected:
		virtual ~Group(){}
	};
}
