#pragma once
#include "Component.h"
class NALMAK_DLL Grid :
	public Component
{
public:
	struct Desc
	{

	};
public:
	Grid(Desc* _desc);
	~Grid();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
private:
	LineManager* m_line;
};

