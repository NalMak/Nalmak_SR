#pragma once
#include "Component.h"
class ClimbTerrain :
	public Component
{
public:
	struct Desc
	{
		Terrain* terrain;
	};
public:
	ClimbTerrain(Desc* _desc);
	~ClimbTerrain();
private:
	Terrain* m_targetTerrain;

	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
};

