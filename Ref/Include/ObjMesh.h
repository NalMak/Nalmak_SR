#pragma once
#include "VIBuffer.h"
class NALMAK_DLL ObjMesh final :
	public VIBuffer
{
public:
	ObjMesh();
	virtual ~ObjMesh();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;

private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();


public:
	void SetFilePath(const wstring& _fp) { m_filePath = _fp; }

private:
	wstring m_filePath;

};

