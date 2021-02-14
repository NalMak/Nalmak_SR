#pragma once

#ifndef __RENDERTARGET_H__
#define __RENDERTARGET_H__

#include "IResource.h"

//https://m.blog.naver.com/PostView.nhn?blogId=sorkelf&logNo=40156769867&proxyReferer=https:%2F%2Fwww.google.com%2F
// ��Ƽ�н� ������ ����

BEGIN(Nalmak)
class NALMAK_DLL RenderTarget :
	public IResource
{
	friend class ResourceManager;
public:
	RenderTarget();
	~RenderTarget();
private:
	RenderTarget(UINT _width, UINT _height, D3DFORMAT _format, DWORD _color);
private:
	// IResource��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp) override;
	virtual void Release() override;

public:
	PDIRECT3DTEXTURE9 GetTexture() const { assert("Render Texture is nullptr!" && m_texture); return m_texture; }
	void StartRecord(UINT _index);
	void EndRecord();
	UINT GetTargetIndex() { return m_targetIndex; }
private:
	PDIRECT3DTEXTURE9 m_texture = nullptr;
	LPDIRECT3DSURFACE9 m_captureSurface = nullptr; // �Ӹ� �ϳ��� �ϳ��� ���ǽ�
	LPDIRECT3DSURFACE9 m_originSurface = nullptr;
	UINT m_targetIndex;
	DWORD m_color;
};
END
#endif // !__RENDERTARGET_H__
