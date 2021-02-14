
// Nalmak3D_EffectToolView.cpp : CNalmak3D_EffectToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Nalmak3D_EffectTool.h"
#endif

#include "Nalmak3D_EffectToolDoc.h"
#include "Nalmak3D_EffectToolView.h"
#include "MainFrm.h"
#include "BaseScene.h"
#include "ParticleObjectManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
// CNalmak3D_EffectToolView

IMPLEMENT_DYNCREATE(CNalmak3D_EffectToolView, CView)

BEGIN_MESSAGE_MAP(CNalmak3D_EffectToolView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CNalmak3D_EffectToolView ����/�Ҹ�

CNalmak3D_EffectToolView::CNalmak3D_EffectToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CNalmak3D_EffectToolView::~CNalmak3D_EffectToolView()
{
	
	Core::DestroyInstance();
}

BOOL CNalmak3D_EffectToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CNalmak3D_EffectToolView �׸���

void CNalmak3D_EffectToolView::OnDraw(CDC* /*pDC*/)
{
	CNalmak3D_EffectToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Core::GetInstance()->Run();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CNalmak3D_EffectToolView �μ�

BOOL CNalmak3D_EffectToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CNalmak3D_EffectToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CNalmak3D_EffectToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CNalmak3D_EffectToolView ����

#ifdef _DEBUG
void CNalmak3D_EffectToolView::AssertValid() const
{
	CView::AssertValid();
}

void CNalmak3D_EffectToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNalmak3D_EffectToolDoc* CNalmak3D_EffectToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNalmak3D_EffectToolDoc)));
	return (CNalmak3D_EffectToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CNalmak3D_EffectToolView �޽��� ó����


void CNalmak3D_EffectToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMainFrame* mainFrame = (CMainFrame*)::AfxGetApp()->GetMainWnd();
	RECT frameRect = {};
	RECT thisRect = {};
	mainFrame->GetWindowRect(&frameRect);
	GetClientRect(&thisRect);

	mainFrame->SetWindowPos(nullptr,
		0, 0,
		WINCX + frameRect.right - frameRect.left - thisRect.right,
		WINCY + frameRect.bottom - frameRect.top - thisRect.bottom,
		SWP_NOSIZE | SWP_NOMOVE);


	g_hWnd = m_hWnd;

	Core::Desc core;
	core.wincx = WINCX;
	core.wincy = WINCY;
	core.resourceDirectoryPath = L"../Resource/";
	Core::GetInstance()->Initialize(m_hWnd,&core);
	Core::GetInstance()->AddScene(L"scene", Scene::Instantiate<BaseScene>());
	Core::GetInstance()->SetStartScene(L"scene");

	SetTimer(1, 16, NULL);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CNalmak3D_EffectToolView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Invalidate(false);
	
	CView::OnTimer(nIDEvent);
}
