#include "stdafx.h"
#include "..\Include\StageScene.h"
#include "Nalmak_Include.h"

#include "NextSceneLoad.h"


void StageScene::Initialize()
{
	auto cam = INSTANTIATE()->AddComponent<Camera>();
	cam->GetTransform()->position = Vector3(0, 0, -1.f);
	MeshRenderer::Desc render;
	auto obj1 = INSTANTIATE()->AddComponent<MeshRenderer>(&render);
	obj1->SetScale(Vector3(1, 1, 3));
}
