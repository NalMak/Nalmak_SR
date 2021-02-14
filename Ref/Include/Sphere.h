#pragma once
#include "VIBuffer.h"
class Sphere :
	public VIBuffer
{
public:
	Sphere();
	~Sphere();

	// VIBuffer��(��) ���� ��ӵ�
	virtual void Initialize(wstring _fp = L"") override;
private:
	virtual void CreateVertexBuffer();
	virtual void CreateIndexBuffer();
private:
	int m_heightSliceCount;
	int m_widthSliceCount;
	float m_radius;
};

