
// Nalmak3D_EffectTool.h : Nalmak3D_EffectTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CNalmak3D_EffectToolApp:
// �� Ŭ������ ������ ���ؼ��� Nalmak3D_EffectTool.cpp�� �����Ͻʽÿ�.
//

class CNalmak3D_EffectToolApp : public CWinAppEx
{
public:
	CNalmak3D_EffectToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	DECLARE_MESSAGE_MAP()
};

extern CNalmak3D_EffectToolApp theApp;
