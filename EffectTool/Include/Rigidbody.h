#pragma once

#ifndef __RIGIDBODY_H__
#define __RIGIDBODY_H__

#include "Component.h"
class NALMAK_DLL Rigidbody :
	public Component
{
public:
	struct Desc
	{
		float mass = 10.f;							// ����
		float dragCoefficient = 0.04f;				// ������ ��ü�� ���װ��? https://t1.daumcdn.net/cfile/tistory/990E98405D352AA208
		float gravityDragCoefficient = 0.42f;
		float torqueDragCoefficient = 0.2f;
		float radius = 5.f;							// ��ü ������
		float gravityRate = 1.f;					// �߷� ����

		bool isGravity = true;
		bool isAirDrag = false;
		bool isGravityDrag = false;
		bool isTorqueDrag = true;
	};
public:
	Rigidbody(Desc* _desc);
	~Rigidbody();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate()override;

	void IntegrateForce(float deltaTime);			// �� -> �ӵ�
	void IntegrateAngularForce(float deltaTime);	// torque -> ���ӵ�

private:
	Vector3 m_position;			// rigidbody�� position, transform position (before new update)
	float m_inverseMass;		// ������ ����
	float m_airDragCoefficient;	// ���� ���� ���� ���
	float m_gravityDragCoefficient;// �߷� ���� ��� (��ü)

	Vector3 m_force;			// �޴� �ܺ���
	Vector3 m_dragForce;		// ���� ��
	Vector3 m_velocity;			// ���ӵ�

	Vector3 m_torque;			// ��ũ, ȸ����?
	Vector3 m_dragTorque;		// ���� ��ũ
	Vector3 m_angularVelocity;	// ���ӵ�
	float m_InverseInertia;		// ���� �ټ�???
	float m_torqueDragCoefficient; // ȸ�� ���� ��� -> ���� ���ǰ�

	bool m_isGravity;			// �߷� on, off
	bool m_isAirDrag;			// �������� on, off
	bool m_isGravityDrag;		// �߷����� on, off
	bool m_isTorqueDrag;		// ȸ������ on, off

	float m_gravityRate;

public:
	void SetForce(const Vector3& _force) { m_force = _force; }
	void AddForce(const Vector3& _force) { m_force += _force; }		// AddForce�� ��𼱰� �ܺο��� �Ѵ�
	void AddForceForward(float _power);

	void SetVelocity(const Vector3& _velocity) { m_velocity = _velocity; }
	void SetVelocityX(const float& _x) { m_velocity.x = _x; }
	void SetVelocityY(const float& _y) { m_velocity.y = _y; }
	void SetVelocityZ(const float& _z) { m_velocity.z = _z; }

	void AddTorque(const Vector3& _torque) { m_torque += _torque; }
	void SetAngularVelocity(const Vector3& _velocity) { m_angularVelocity = _velocity; }

	void SetActiveGravity(bool _active) { m_isGravity = _active; }
	void SetActiveAirDrag(bool _active) { m_isAirDrag = _active; }
	void SetActiveGravityDrag(bool _active) { m_isGravityDrag = _active; }

public:
	const Vector3& GetForce() { return m_force; }
	const Vector3& GetVelocity() { return m_velocity; }

	const Vector3& GetTorque() { return m_torque; }
	const Vector3& GetAngularVelocity() { return m_angularVelocity; }

};

#endif // !__RIGIDBODY_H__
