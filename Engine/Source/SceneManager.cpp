#include "..\Include\SceneManager.h"
#include "ObjectManager.h"
#include "RenderManager.h"
#include "LineManager.h"
IMPLEMENT_SINGLETON(SceneManager)

// ��� Scene�� ������ ����,����,����
// AddScene :���ο� Scene���
// Load : ���� Scene�̵� ����
// CompareCurrentScene : ���� Scene�� �̸��� ��
// SetFirstScene : ���� Scene����
void SceneManager::LoadNextScene()
{
	if (m_isLoad)
	{
		m_isLoad = false;
		ObjectManager::GetInstance()->ReleaseScene();

		assert("Next Scene is Empty" && m_nextScene);
		m_currentScene = m_nextScene;
		m_currentScene->Initialize();
	}
}

SceneManager::~SceneManager()
{
	Release();
}

HRESULT SceneManager::Initialize()
{
	m_isLoad = false;
	m_sceneChangerTimer = 0.f;
	return S_OK;
}

void SceneManager::Update()
{
	LoadNextScene();

	assert(m_currentScene);
	ObjectManager::GetInstance()->Update();
}

void SceneManager::LateUpdate()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->LateUpdate();
}

void SceneManager::Release()
{
	for (auto& scene : m_sceneList)
		SAFE_DELETE(scene.second);

	ObjectManager::GetInstance()->Release();
	RenderManager::GetInstance()->Release();
}

void SceneManager::PreRender()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->PreRender();
	//LineManager::GetInstance()->DeleteLines();
}

void SceneManager::Render()
{
	assert(m_currentScene);

	RenderManager::GetInstance()->Render();
}

void SceneManager::PostRender()
{
	assert(m_currentScene);

	ObjectManager::GetInstance()->PostRender();
	LineManager::GetInstance()->DeleteLines();
}

void SceneManager::SetFirstScene(const wstring&  _name)
{
	m_currentScene = m_sceneList[_name];
	assert(m_currentScene);
	m_currentScene->Initialize();
}

void SceneManager::Load(const wstring& _name)
{
	m_nextScene = m_sceneList[_name];
	m_isLoad = true;
	assert("Load Scene Fail! Please Check Scene name or Create Scene in mainGame!" && m_nextScene);
}

void SceneManager::AddScene(const wstring&  _name, Scene* _scene)
{
	if (m_sceneList[_name])
	{
		assert(0 && L"Scene name is already exist");
	}

	m_sceneList[_name] = _scene;
}

bool SceneManager::CompareCurrentScene(const wstring&  _name)
{
	return m_sceneList[_name] == m_currentScene;
}
