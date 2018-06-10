#include "Scene.h"
#include "RenderWindow.h"

namespace pallas
{
	void Scene::AddSceneGraphNode(SceneGraphNode* SceneGraphNode) {
		mSceneGraphNodes.push_back(SceneGraphNode);
	}
	int Scene::GetNumSceneGraphNode() {
		return mSceneGraphNodes.size();
	}
	SceneGraphNode* Scene::GetSceneGraphNode(int index) {
		return mSceneGraphNodes[index].get();
	}
	void Scene::RemoveSceneGraphNode(SceneGraphNode* pnode) {
        for (auto itr = mSceneGraphNodes.begin(); itr != mSceneGraphNodes.end(); ++itr) {
            if (itr->get()->GetID() == pnode->GetID()) {
                mSceneGraphNodes.erase(itr);
                break;
            }
        }
	}

	void Scene::AddCamera(Camera* camera) {
		mCameras.push_back(camera);
	}
	int Scene::GetNumCamera() {
		return mCameras.size();
	}
	Camera* Scene::GetCamera(int index) {
		return mCameras[index].get();
	}
	void Scene::RemoveCamera(Camera* camera) {
		for (auto itr = mCameras.begin(); itr != mCameras.end(); ++itr) {
			if (itr->get()->GetID() == camera->GetID()) {
				mCameras.erase(itr);
				break;
			}
		}
	}

	void Scene::AddLightSource(LightSource* lightSource) {
		mLightSources.push_back(lightSource);
	}
	int Scene::GetNumLightSource() {
		return mLightSources.size();
	}
	LightSource* Scene::GetLightSource(int index) {
		return mLightSources[index].get();
	}
	void Scene::RemoveLightSource(LightSource* lightSource) {
		for (auto itr = mLightSources.begin(); itr != mLightSources.end(); ++itr) {
			if (itr->get()->GetID() == lightSource->GetID()) {
				mLightSources.erase(itr);
				break;
			}
		}
	}


	void Scene::handleEvent() {
		for (auto itr_camera : mCameras) {
			auto renderTarget = itr_camera->GetRenderTarget();
			if (renderTarget != nullptr && renderTarget->asRenderWindow()) {
				renderTarget->asRenderWindow()->DispatchEvents();
			}
		}
	}

	void Scene::update() {
		for (auto itr_camera : mCameras) {
			//auto cameraManipulator = itr_camera->GetManipulator();
			std::vector<pallas::SceneGraphNode*> nodes;
			itr_camera->GetCullingNodes(nodes);
			for (auto itr_node : nodes) {
				itr_node->Update();
			}
		}
	}

	void Scene::cull() {
		clearRenderStage();
		for (auto itr : mCameras) {
			itr->Cull(this);
		}
	}

	void Scene::render() {
		for (auto itr : mRenderStages) {
			mRenderer->Render(itr.get());
		}
	}

	void Scene::addRenderStage(RenderStage* renderStage) {

	}
	void Scene::clearRenderStage() {

	}

	void Scene::RenderOneFrame() {
		handleEvent();
		update();
		cull();
		render();
	}
}