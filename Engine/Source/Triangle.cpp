#include "..\Include\Triangle.h"





void Triangle::Initialize(wstring _fp)
{
	CreateVertexBuffer();
	CreateIndexBuffer();

	SetFigureCount(1);
	SetVertexCount(3);
}

void Triangle::CreateVertexBuffer()
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * 3,
		0, // ��ƼŬ�̳� ���� �ɼ� ����
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));

	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0].position = Vector3(-0.5f, -0.5f, 0.f);
	vertices[0].uv = Vector2(0.f, 1.f);
	vertices[0].normal = Vector3(0.f, 0.f, 1.f);

	vertices[1].position = Vector3(0.f, 0.36f, 0.f);
	vertices[1].uv = Vector2(1.f, 0.f);
	vertices[1].normal = Vector3(0.f, 0.f, 1.f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0.f);
	vertices[2].uv = Vector2(1.f, 1.f);
	vertices[2].normal = Vector3(0.f, 0.f, 1.f);


	m_vBuffer->Unlock();

	D3DXComputeBoundingSphere(&vertices[0].position, 3, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);

}

void Triangle::CreateIndexBuffer()
{
	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * 3,
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* indices = nullptr;

	m_iBuffer->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	m_iBuffer->Unlock();
}
