#pragma once
#include "Component.h"
class PlaneController :
	public Component
{
public:
	struct Desc {

	};

public:
	PlaneController(Desc* _desc);
	~PlaneController();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:


	// move, ������, ȸ�� �ռ�
	void MoveLeft();
	void MoveRight();
	void MoveFront();

	void MoveUp();
	void MoveDown();

	void RecoverRotateHorizotal();
private:
	float m_horizontalLevel = 0;
private:
	Rigidbody* m_rigidbody;
	class PlaneInfo* m_planeInfo;
	InputManager* m_input;
};

