#pragma once
#include "Component.h"
class NALMAK_DLL DrawGizmo :
	public Component
{
public:
	struct Desc
	{

	};
public:
	DrawGizmo(Desc* _desc);
	~DrawGizmo();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	LineManager* m_line;
};

