#pragma once
#include "GraphicWindow.h"
#include "..\PallasCore\Scene.h"
#include "..\PallasCore\VertexData.h"
#include "..\PallasCore\Material.h"
#include "..\PallasCore\Camera.h"
#include "..\PallasCore\RenderStage.h"
#include "..\PallasCore\RenderQueue.h"
#include "..\PallasCore\Mesh.h"
#include "..\PallasCore\LightSource.h"
#include "..\PallasVKRenderSystem\VKRenderer.h"

class VKGraphicWindow : public GraphicWindow
{
public:
	virtual bool PrepareRender() override { 
		mScene = new pallas::Scene();
		//
		{
			auto mesh1 = new pallas::Mesh();
			//
			auto pvertexArray = new pallas::RefVecArray3f(3);
			pvertexArray->at(0) = pallas::Vec3f(-10, -10, 0);
			pvertexArray->at(1) = pallas::Vec3f(10, -10, 0);
			pvertexArray->at(2) = pallas::Vec3f(0, 10, 0);
			mesh1->SetVertexArray(pvertexArray);
			//
			auto pnormalArray = new pallas::RefVecArray3f(3, pallas::Vec3f(0, 0, 1));
			mesh1->SetNormalArray(pnormalArray);
			//
			auto pcolorArray = new pallas::RefVecArray4f(3);
			pcolorArray->at(0) = pallas::Vec4f(1.0, 0.0, 0.0, 1.0);
			pcolorArray->at(1) = pallas::Vec4f(0.0, 1.0, 0.0, 1.0);
			pcolorArray->at(2) = pallas::Vec4f(0.0, 0.0, 1.0, 1.0);
			mesh1->AddColorArray(pcolorArray);
			//
			auto ptexCoord = new pallas::RefVecArray2f(3);
			ptexCoord->at(0) = pallas::Vec2f(0, 0);
			ptexCoord->at(1) = pallas::Vec2f(1, 0);
			ptexCoord->at(2) = pallas::Vec2f(0.5, 1);
			mesh1->AddTextureCoords(ptexCoord);
			//
			mesh1->SetPrimitiveType(pallas::PrimitiveType::PT_TRIANGLES);
			//
			mScene->AddSceneGraphNode(mesh1);
		}
		//
		auto camera = new pallas::Camera();
		pallas::Mat4d vM, pM;
		vM.makeLookAt(pallas::Vec3d(0, 0, 10), pallas::Vec3d(0, 0, 0), pallas::Vec3d(0, 1, 0));
		pM.makePerspective(45, 1.0, 1.0, 100);
		camera->SetViewMatrix(vM);
		camera->SetProjectionMatrix(pM);
		mScene->AddCamera(camera);
		//
		auto light = new pallas::DirectLight();
		mScene->AddLightSource(light);
		//
		mScene->SetRenderer(new pallas::VKRenderer());
		//
		return true;
	}

	virtual void Render() override {
		mScene->RenderOneFrame();
	}
private:
	pallas::ref_ptr<pallas::Scene> mScene;
};