#pragma once
#include <string>
#include <atomic>
#include <vector>
#include "SceneNode.h"
#include "Material.h"
#include "Transform.h"
#include "..\PallasGFL\BoundingBox.h"
#include "..\PallasGFL\BoundingSphere.h"

namespace pallas
{
	typedef gfl::BoundingSphere BoundingSphere;
	typedef gfl::BoundingBox BoundingBox;
	//
    class Group;
    typedef std::vector<Group*> NodePath;
    typedef std::vector<NodePath> NodePathList;
    //
	class RenderStage;
	class PALLASCORE_API SceneGraphNode : public SceneNode
	{
        friend class Group;
	public:
		class UpdateCallBack : public Object
		{
			friend class SceneGraphNode;
		public:
			virtual void run() {

			}
		};
	private:
		class UpdateGraphNode : public Referenced
		{
		public:
			void AddUpdateCallBack(UpdateCallBack* callBack) {
				mUpdateCallBacks.push_back(callBack);
			}

			void RemoveUpdateCallBack(UpdateCallBack* callBack) {
				for (auto itr = mUpdateCallBacks.begin(); itr != mUpdateCallBacks.end(); ++itr) {
					if (itr->get()->GetID() == callBack->GetID()) {
						mUpdateCallBacks.erase(itr);
						break;
					}
				}
			}

			int GetNumUpdateCallBack() {
				return mUpdateCallBacks.size();
			}

			UpdateCallBack* GetUpdateCallBack(int index) {
				return mUpdateCallBacks[index].get();
			}


			void AddChild(UpdateGraphNode* pchild) {
				mChildren.push_back(pchild);
			}

			int GetNumChildren() {
				return mChildren.size();
			}

			UpdateGraphNode* GetChild(int index) {
				return mChildren[index];
			}

			bool ContainsNode(UpdateGraphNode* pnode) {
				for (auto itr : mChildren) {
					if (itr == pnode)
						return true;
				}
				return false;
			}

			void RemoveChild(UpdateGraphNode* pnode) {
				for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
					if (*itr == pnode) {
						mChildren.erase(itr);
						return;
					}
				}
			}

			void Update() {
				for (auto itr_callBack : mUpdateCallBacks) {
					itr_callBack->run();
				}
				//
				for (auto itr_child : mChildren) {
					itr_child->Update();
				}
			}
		private:
			std::vector<ref_ptr<UpdateCallBack>> mUpdateCallBacks;
			std::vector<UpdateGraphNode*> mChildren;
		};
	public:
		enum State
		{
			NST_NORMAL = 0x0000000,
			NST_DELETED = 0x0000001,
			NST_UNVISIBLE = 0x0000002
		};
	public:
		SceneGraphNode() {
			AddAttribute(new Transform());
		}

		virtual void SetState(State state) {
			mState.store(state);
		}

		virtual unsigned long long GetState() {
			return mState.load();
		}

        virtual int GetNumParent() {
            return mParents.size();
        }

        virtual Group* GetParent(int index) {
            return mParents[index];
        }

        virtual void SetMaterial(Material* material) {
			if (material != nullptr)
				AddAttribute(material);
			else
				RemoveAttribute("material");
        }

        virtual Material* GetMaterial() {
			return (Material*)GetAttribute("material");
        }

		virtual Transform* GetTransform() {
			return (Transform*)GetAttribute("transform");
		}

		virtual  BoundingSphere GetBoundingSphere();
		virtual  BoundingBox GetBoundingBox();
		virtual void AddUpdateCallBack(UpdateCallBack* updateCallBack);
		virtual void RemoveUpdateCallBack(UpdateCallBack* updateCallBack);
		virtual int GetNumUpdateCallBak();
		virtual UpdateCallBack* GetUpdateCallBack(int index);
		virtual void Update();
		virtual void Cull(RenderStage* renderStage);
	protected:
		virtual ~SceneGraphNode() {}
        virtual void addParent(Group* p) {
            mParents.push_back(p);
			mountUpdateGraphNode();
        }
        virtual void removeParent(Group* p) {
            auto parentNode = (SceneGraphNode*)p;
			for (auto itr = mParents.begin(); itr != mParents.end(); ++itr) {
				if (*itr == p) {
					mParents.erase(itr);
					break;
				}
			}
        }
	protected:
		std::atomic<unsigned long long> mState;
        std::vector<Group*> mParents;
		pallas::ref_ptr<UpdateGraphNode> mUpdateGraphNode;
        pallas::ref_ptr<Material> mMaterial;
	private:
		void mountUpdateGraphNode();
		void unMountUpdateGraphNode();
	};
}
