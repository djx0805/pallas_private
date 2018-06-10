#pragma once
#include <vector>
#include "Camera.h"
#include "LightSource.h"
#include "RenderStage.h"
#include "Renderer.h"

namespace pallas
{
	class PALLASCORE_API Scene : public Referenced
	{
		friend class Camera;
    public:
        //static pallas::ref_ptr<Scene> NewSharedScene();
	public:
		Scene() {}
		//
		virtual void AddSceneGraphNode(SceneGraphNode* SceneGraphNode);
		virtual int GetNumSceneGraphNode();
		virtual SceneGraphNode* GetSceneGraphNode(int index);
		virtual void RemoveSceneGraphNode(SceneGraphNode* pnode);
		//
		virtual void AddCamera(Camera* camera);
		virtual int GetNumCamera();
		virtual Camera* GetCamera(int index);
		virtual void RemoveCamera(Camera* camera);
		//
		virtual void AddLightSource(LightSource* lightSource);
		virtual int GetNumLightSource();
		virtual LightSource* GetLightSource(int index);
		virtual void RemoveLightSource(LightSource* lightSource);
        //
		virtual void SetRenderer(Renderer* renderer) {
			mRenderer = renderer;
		}
		virtual Renderer* GetRenderer() {
			return mRenderer.get();
		}
        virtual void RenderOneFrame();
	protected:
		virtual ~Scene() {}
		virtual void handleEvent();
        virtual void update();
        virtual void cull();
		virtual void render();
		virtual void Scene::addRenderStage(RenderStage* renderStage);
		virtual void Scene::clearRenderStage();
	protected:
		std::vector<pallas::ref_ptr<SceneGraphNode>> mSceneGraphNodes;
		std::vector<pallas::ref_ptr<Camera>> mCameras;
		std::vector<pallas::ref_ptr<LightSource>> mLightSources;
		std::vector < pallas::ref_ptr<RenderStage>> mRenderStages;
		pallas::ref_ptr<Renderer> mRenderer;
	};
}
