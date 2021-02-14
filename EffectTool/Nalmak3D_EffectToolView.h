
// Nalmak3D_EffectToolView.h : CNalmak3D_EffectToolView Ŭ������ �������̽�
//

#pragma once

class CNalmak3D_EffectToolDoc;

class CNalmak3D_EffectToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CNalmak3D_EffectToolView();
	DECLARE_DYNCREATE(CNalmak3D_EffectToolView)

// Ư���Դϴ�.
public:
	CNalmak3D_EffectToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CNalmak3D_EffectToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // Nalmak3D_EffectToolView.cpp�� ����� ����
inline CNalmak3D_EffectToolDoc* CNalmak3D_EffectToolView::GetDocument() const
   { return reinterpret_cast<CNalmak3D_EffectToolDoc*>(m_pDocument); }
#endif

