#pragma once
#include "VIBuffer.h"
class Box :
	public VIBuffer
{
public:
	Box();
	~Box();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
};

