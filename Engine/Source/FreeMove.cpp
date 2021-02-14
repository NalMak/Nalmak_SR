#include "..\Include\FreeMove.h"
#include "Transform.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "Camera.h"

FreeMove::FreeMove(Desc * _desc)
{
	m_keyMoveSpeed = _desc->keyMoveSpeed;
	m_mouseSensitive = _desc->mouseSensitive;
	m_scrollSpeed = _desc->scrollSpeed;
	m_wheelMoveSpeed = _desc->wheelMoveSpeed;

}

void FreeMove::Initialize()
{
	m_input = InputManager::GetInstance();
	m_camera = GetComponent<Camera>();

	Vector3 eulerRot = m_transform->GetEulerRotation();
	m_xRot = Deg2Rad * eulerRot.x;
	m_yRot = Deg2Rad * eulerRot.y;
}

void FreeMove::Update()
{
	//DEBUG_LOG(L"Free Move", m_transform);

	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_ALT))
		MouseInput_Alt();
	else
		MouseInput();

	WheelInput();
	ArrowInput();
}

void FreeMove::MouseInput()
{
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_LEFT_MOUSE))
	{
		// object select
		//Vector3 point = m_transform->GetWorldPosition();

	}
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_RIGHT_MOUSE))
	{
		// rotate		
		Rotate(m_input->GetMouseMoveDir());
	}
}

void FreeMove::MouseInput_Alt()
{
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_LEFT_MOUSE))
	{
		// rotate
		Rotate(m_input->GetMouseMoveDir());

	}
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_RIGHT_MOUSE))
	{
		// zoom	
		Zoom(m_input->GetMouseMoveDir());
	}
}

void FreeMove::WheelInput()
{
	// scroll ......
	int wheelScroll = InputManager::GetInstance()->GetWheelScroll();
	if (wheelScroll != 0)
	{
		Vector2 dir;
		if (wheelScroll > 0)
			dir = Vector2(1.f, 1.f);
		else
			dir = Vector2(-1.f, -1.f);

		Zoom(dir * m_scrollSpeed);
		InputManager::GetInstance()->SetWheelScroll(0);
	}

	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_WHEEL_MOUSE))
	{
		// move	
		Vector2 dir2 = m_input->GetMouseMoveDir();
		Vector3 dir3 = Vector3(-dir2.x, -dir2.y, 0.f);
		Move(dir3 * m_wheelMoveSpeed);
	}
}

void FreeMove::ArrowInput()
{
	Vector3 dir = Vector3(0.f, 0.f, 0.f);

	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_UP_ARROW) || m_input->GetKeyPress(KEY_STATE::KEY_STATE_W))
	{
		dir += Vector3(0.f, 0.f, 1.f);
	}
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_DOWN_ARROW) || m_input->GetKeyPress(KEY_STATE::KEY_STATE_S))
	{
		dir -= Vector3(0.f, 0.f, 1.f);
	}
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_LEFT_ARROW) || m_input->GetKeyPress(KEY_STATE::KEY_STATE_A))
	{
		dir -= Vector3(1.f, 0.f, 0.f);
	}
	if (m_input->GetKeyPress(KEY_STATE::KEY_STATE_RIGHT_ARROW) || m_input->GetKeyPress(KEY_STATE::KEY_STATE_D))
	{
		dir += Vector3(1.f, 0.f, 0.f);
	}

	D3DXVec3Normalize(&dir, &dir);
	Move(dir * m_keyMoveSpeed);
}

void FreeMove::Move(Vector3 _dir)
{
	Vector3 right = m_transform->GetRight() * _dir.x;
	Vector3 up = m_transform->GetUp() * _dir.y;
	Vector3 forward = m_transform->GetForward() * _dir.z;
	m_transform->position += (right + up + forward) * dTime;
}


void FreeMove::Rotate(Vector2 _dir)
{
	m_xRot -= Deg2Rad * _dir.y * m_mouseSensitive;
	m_yRot += Deg2Rad * _dir.x * m_mouseSensitive;
	Quaternion rot;

	D3DXQuaternionRotationYawPitchRoll(&rot, m_yRot, m_xRot, 0.f);
	m_transform->rotation = rot;
}

void FreeMove::Zoom(Vector2 _dir)
{
	// �����
	//float amount = D3DX_PI * (_dir.x / RenderManager::GetInstance()->GetWindowWidth());
	//m_camera->AddFovY(amount);
	//m_camera->UpdateFovY();

	float len = 0.f;

	if (0.f > _dir.x + _dir.y)
		len = D3DXVec2Length(&_dir);
	else
		len = -D3DXVec2Length(&_dir);

	Vector3 forward = m_transform->GetForward() * len;
	m_transform->position += forward * dTime;
}
