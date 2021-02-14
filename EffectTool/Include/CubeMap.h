#pragma once
#include "Component.h"
class Transform;

class CubeMap :
	public Component
{
public:
	struct Desc
	{
		
	};
public:
	CubeMap(Desc* _desc);
	~CubeMap();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	Transform* m_mainCam;
};

