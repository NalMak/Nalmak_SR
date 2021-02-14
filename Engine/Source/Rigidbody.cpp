#include "Rigidbody.h"
#include "Transform.h"

Rigidbody::Rigidbody(Desc * _desc)
{
	m_inverseMass = 1.f / _desc->mass;
	m_airDragCoefficient = _desc->dragCoefficient;
	m_gravityDragCoefficient = _desc->gravityDragCoefficient;
	m_torqueDragCoefficient = _desc->torqueDragCoefficient;
	m_InverseInertia = 5.f / (2.f * _desc->mass * (_desc->radius * _desc->radius));
	m_gravityRate = _desc->gravityRate;

	m_isGravity = _desc->isGravity;
	m_isAirDrag = _desc->isAirDrag;
	m_isGravityDrag = _desc->isGravityDrag;
	m_isTorqueDrag = _desc->isTorqueDrag;
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Initialize()
{
	m_force = Vector3(0.f, 0.f, 0.f);
	m_dragForce = Vector3(0.f, 0.f, 0.f);
	m_velocity = Vector3(0.f, 0.f, 0.f);

	m_torque = Vector3(0.f, 0.f, 0.f);
	m_dragTorque = Vector3(0.f, 0.f, 0.f);
	m_angularVelocity = Vector3(0.f, 0.f, 0.f);
}

void Rigidbody::Update()
{
}

void Rigidbody::LateUpdate()
{
	float deltaTime = TimeManager::GetInstance()->GetdeltaTime();
	IntegrateForce(deltaTime);
	IntegrateAngularForce(deltaTime);
}

void Rigidbody::IntegrateForce(float deltaTime)
{
	// ���� ������ �ռ��� ������ �ܺο��� Addforce ȣ���ϸ鼭 ��

	// �߷� ����
	if (m_isGravityDrag)
	{
		if (m_velocity.y < 0.f)
		{
			Vector3 verticalVelocity = Vector3(0.f, m_velocity.y, 0.f);
			Vector3 gravityDrag = -verticalVelocity * m_gravityDragCoefficient;
			m_dragForce += gravityDrag;
		}
	}

	// ���� ���� ����
	if (m_isAirDrag)
	{
		Vector3 horizontalVelocity = Vector3(m_velocity.x, 0.f, m_velocity.z);
		Vector3 forwardDrag = -horizontalVelocity * m_airDragCoefficient;
		m_dragForce += forwardDrag;
	}

	// �߷� ����
	if (m_isGravity)
	{
		Vector3 gravityForce = Vector3(0.f, -9.8f * m_gravityRate / m_inverseMass, 0.f);
		AddForce(gravityForce);
	}

	// �ӵ� ���
	Vector3 positiveAccel = m_force * m_inverseMass;		// ���ӵ�
	Vector3 nagativeAccel = m_dragForce * m_inverseMass;	// �ݰ��ӵ�
	m_velocity += (positiveAccel + nagativeAccel) * deltaTime;

	m_transform->position += m_velocity * deltaTime; // �̵�
	m_force = Vector3(0.f, 0.f, 0.f);
	m_dragForce = Vector3(0.f, 0.f, 0.f);
	//m_velocity = Vector3(0.f, 0.f, 0.f);
}

void Rigidbody::IntegrateAngularForce(float deltaTime)
{
	// ȸ�� ����
	if (m_isTorqueDrag)
	{
		Vector3 torqueDrag = -m_angularVelocity * m_torqueDragCoefficient;
		m_dragTorque += torqueDrag;
	}

	Vector3 positiveAccel = m_torque * m_InverseInertia;		// �� ���ӵ�
	Vector3 positiveVelocity = positiveAccel * deltaTime;		// �ӵ�
	Vector3 nagativeAccel = m_dragTorque * m_InverseInertia;	// �ݰ��ӵ�
	Vector3 nagativeVelocity = nagativeAccel * deltaTime;		// �ݼӵ�
	m_angularVelocity += positiveVelocity + nagativeVelocity;

	// ȸ��
	Quaternion rot;
	D3DXQuaternionRotationYawPitchRoll(&rot, m_angularVelocity.y * deltaTime, m_angularVelocity.x * deltaTime, m_angularVelocity.z * deltaTime);
	m_transform->rotation *= rot;
	m_torque = Vector3(0.f, 0.f, 0.f);
	m_dragTorque = Vector3(0.f, 0.f, 0.f);
	//m_angularVelocity = Vector3(0.f, 0.f, 0.f);

}


void Rigidbody::AddForceForward(float _power)
{
	Vector3 forward = m_transform->GetForward();
	AddForce(forward * _power);
}
