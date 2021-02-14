#pragma once

#ifndef  __RENDERMANAGER_H__
#define __RENDERMANAGER_H__

#include "Nalmak_Include.h"
#include "Camera.h"

class IRenderer;
class GameObject;
class Material;
class Shader;
class VIBuffer;
class Text;
class Camera;
class DebugManager;
BEGIN(Nalmak)

// ���� ��� 
// IRenderer�� ��ӹ��� ������Ʈ���� �� �Ŵ������� ���������� �Ѱ��ְ�
// �Ŵ����� ������ �������� �������� �ǽ��Ѵ�

// ������ �� �� ������ ��ȭ�� ������ ��ȭ�� �ִٸ� ����̽��� ������ �ٲ��ش�

// �ΰ� ���� . ȭ���ػ� ����, ī�޶� ����Ʈ


// ������ ������ ���׸��󿡼� ���� ���� �ϴ� (0 ~ 5000)������ ���� 
// �⺻ ���� 
//#define RENDER_QUEUE_BACKGROUND 1000
//#define RENDER_QUEUE_GEOMETRY 2000
//#define RENDER_QUEUE_TRANSPARENT 3000
//#define RENDER_QUEUE_OVERLAY 4000


//http://ozlael.egloos.com/2423070 ���۵� ������ �ڷ�
//https://portsnake.tistory.com/253


// Texture coverage 
class RenderManager
{
	DECLARE_SINGLETON(RenderManager)
public:
	RenderManager();
	~RenderManager();

public:
	void Release();
	void Initialize(UINT _wincx,UINT _wincy);
	void Render();
	void Render(Camera* _cam);
	void RenderText();
	void Reset();
private:
	map<int, vector<IRenderer*>> m_renderLists;
	vector<Text*> m_textRenderList;
public:
	void RenderRequest(IRenderer* _render);
	void RenderRequest(Text* _text);
public:
	void AddCamera(Camera* _cam);
	void AddCamera(GameObject* _cam);

private:
	list<Camera*> m_cameraList;
	PDIRECT3DDEVICE9 m_device = nullptr;

private:
	Material* m_currentMaterial; // ����ȭ.. Material���� �׸��� ������ �ּ�ȭ
	VIBuffer* m_currentVIBuffer; // Mesh�� �׸��� �ּ�ȭ
	Shader* m_currentShader; // Shader���� �׸��� ���� �ּ�ȭ
	RENDERING_MODE m_renderingMode;
	BLENDING_MODE m_blendingMode;
	FILL_MODE m_fillMode;

private:
	void UpdateMaterial(Material* _material, const Matrix& _viewProj);
	void UpdateRenderingMode(Material * _material);
	void UpdateBlendingMode(Material * _material);
	void UpdateFillMode(Material* _material);
	void UpdateVIBuffer(IRenderer* _renderer);
	void UpdateShader(Shader* _shader);

	void SetWindowSize(UINT _x, UINT _y);
public:
	UINT GetWindowWidth() { return m_wincx; }
	UINT GetWindowHeight() { return m_wincy; }

public:
	Camera* GetMainCamera();
	void DeleteCamera(Camera* _cam);

private:
	UINT m_wincx;
	UINT m_wincy;
	UINT m_halfWincx;
	UINT m_halfWincy;
private:
	DebugManager* m_debugManager;
};

END
#endif // ! __RENDERMANAGER_H__
