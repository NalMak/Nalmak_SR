#include "stdafx.h"
#include "MainGame.h"
#include "Core.h"
#include "TitleScene.h"
#include "StageScene.h"
#include "NextSceneLoad.h"

TimeManager* g_time;
// ������ ���������� 
// ���� - ���� - �� - �ĸ��߷����� - ���� - ���� - Ŭ���� - ����Ʈ - �����Ͷ�����


MainGame::MainGame()
{

}


MainGame::~MainGame()
{
	Core::DestroyInstance();
}

int MainGame::Run()
{
	m_engine = Core::GetInstance();
	g_time = TimeManager::GetInstance();

	ApplicationSetting();

	ReadyResource();

	ReadyPrototype();

	SystemSetting();

	InstantiateDefault();


	MSG msg;
	try
	{
		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			m_engine->Run();
		}

		return (int)msg.wParam;
	}
	catch (Exception& e)
	{
		MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
		assert(0);
		return 0;
	}
}


void MainGame::ApplicationSetting()
{
	Core::Desc core;
	core.OBJECT_TAG_COUNT = OBJECT_TAG::OBJECT_TAG_MAX;
	core.COLLISION_LAYER_COUNT = COLLISION_LAYER_MAX;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.windowMode = true;

	// ��� ���ҽ� �⺻��� �Ń��°� �� �ε���
	core.resourceDirectoryPath;

	m_engine->Initialize(g_hWnd, &core);
}

void MainGame::SystemSetting()
{
	m_engine->ActivateCollisionByLayer(COLLISION_LAYER_DEFAULT, COLLISION_LAYER_DEFAULT);

	m_engine->AddScene(L"title", Scene::Instantiate<TitleScene>());
	m_engine->AddScene(L"stage", Scene::Instantiate<StageScene>());

	m_engine->SetStartScene(L"title");
}

void MainGame::ReadyResource()
{




}

void MainGame::ReadyPrototype()
{




}

void MainGame::InstantiateDefault()
{


}

