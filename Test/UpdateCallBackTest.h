#pragma once
#include "Test.h"
#include "..\PallasCore\Group.h"

class UpdateCallBackTest : public Test
{
public:
	void run() override
	{
		auto root = pallas::ref_ptr<pallas::Group>(new pallas::Group());
		auto child1 = pallas::ref_ptr<pallas::Group>(new pallas::Group());
		root->AddChild(child1);
		child1->AddUpdateCallBack(new pallas::SceneGraphNode::UpdateCallBack());
		//
		auto child2 = pallas::ref_ptr<pallas::Group>(new pallas::Group());
		root->AddChild(child2.get());
		//
		auto child2_1 = pallas::ref_ptr<pallas::Group>(new pallas::Group());
		child2_1->AddUpdateCallBack(new pallas::SceneGraphNode::UpdateCallBack());
		child2->AddChild(child2_1.get());
		//
		child2->RemoveChild(child2_1.get());
	}
};