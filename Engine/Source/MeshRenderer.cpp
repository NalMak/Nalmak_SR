#include "..\Include\MeshRenderer.h"
#include "ResourceManager.h"
#include "Transform.h"
#include "Animator.h"


MeshRenderer::MeshRenderer(Desc * _desc)
{
	m_viBuffer = ResourceManager::GetInstance()->GetResource<VIBuffer>(_desc->meshName);
	if (!_desc->mtrl)
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	else
		m_material = _desc->mtrl;

	m_animator = nullptr;
	m_layer = _desc->layer;
}

void MeshRenderer::Initialize()
{
	m_animator = GetComponent<Animator>();
}

void MeshRenderer::Update()
{
}

void MeshRenderer::LateUpdate()
{
}

void MeshRenderer::Release()
{
}

void MeshRenderer::Render()
{

	Shader* currentShader = m_material->GetShader();
	assert("Current Shader is nullptr! " && currentShader);

	currentShader->SetMatrix("g_world", GetTransform()->GetWorldMatrix());

	if (m_animator)
		GetMaterial()->SetTexture(0, m_animator->GetDiffuseSprite());



	currentShader->CommitChanges();				   // BeginPass ȣ��� �ݵ�� �׸��� ���� ȣ��
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index ��� x)
												   // Type, �̹��� �̿�� �ε���, �ּ� ��������, ȣ��� ���ؽ� ��, �ε��� ���۳����� �б� ������ �ε���, �׸��� ���� ��
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));


}

void MeshRenderer::BindingStreamSource()
{
									 // ��� ���� �ѹ� //  �ּ�               // ������  // ������
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));

	// �����Լ� ���������ο� �ʿ�!
	// m_device->SetFVF()
	
}
