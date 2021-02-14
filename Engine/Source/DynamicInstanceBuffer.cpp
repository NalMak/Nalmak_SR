#include "DynamicInstanceBuffer.h"




DynamicInstanceBuffer::DynamicInstanceBuffer(int _maxCount)
{
	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_PARTICLE) * _maxCount,
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, // ��ƼŬ�̳� ���� �ɼ� ����
		NULL,
		D3DPOOL_DEFAULT, // ���� ���ؽ� ���۴� ���� �޸�Ǯ�� ���� �Ұ�
		&m_vBuffer,
		nullptr
	));
}

void DynamicInstanceBuffer::Initialize(wstring _fp)
{
}

void DynamicInstanceBuffer::CreateVertexBuffer()
{
}

void DynamicInstanceBuffer::CreateIndexBuffer()
{
}

void DynamicInstanceBuffer::UpdateInstanceBuffer(INPUT_LAYOUT_PARTICLE * _instanceList, int _count)
{
	INPUT_LAYOUT_PARTICLE* instanceData = nullptr;

	m_vBuffer->Lock(0, 0, (void**)&instanceData, D3DLOCK_DISCARD);
	memcpy(instanceData, _instanceList, sizeof(INPUT_LAYOUT_PARTICLE)* _count);
	m_vBuffer->Unlock();
}
