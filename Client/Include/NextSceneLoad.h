#pragma once
#include "Component.h"
class NextSceneLoad :
	public Component
{
public:
	struct Desc
	{

	};
public:
	NextSceneLoad(Desc* _desc);
	~NextSceneLoad();

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;
};

