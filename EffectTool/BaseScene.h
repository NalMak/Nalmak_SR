#pragma once
#include "Scene.h"

class BaseScene :
	public Scene
{
public:
	BaseScene();
	~BaseScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Initialize() override;
};

