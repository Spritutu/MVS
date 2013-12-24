
// AOIEDITHelpView.h : CAOIEDITHelpView ��Ľӿ�
//


#pragma once
#include "afxwin.h"
#ifndef _HelpView_H_
#define _HelpView_H_

class CAOIEDITHelpDoc;
class CAOIEDITHelpView : public CFormView
{
protected: // �������л�����
	CAOIEDITHelpView();
	DECLARE_DYNCREATE(CAOIEDITHelpView)

public:
	enum{ IDD = IDD_AOIEDITHELP_FORM };

// ����
public:
	CAOIEDITHelpDoc* GetDocument() const;

// ����
public:
   	HWND GetWndHID(){ASSERT(this->m_hWnd);return m_hWnd;};
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);

// ʵ��
public:
	virtual ~CAOIEDITHelpView();



#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	void SysInit();
protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	bool m_bRBtnDB;
public:
	//CStatic m_halconDispWnd;
};

#ifndef _DEBUG  // AOIEDITHelpView.cpp �еĵ��԰汾
inline CAOIEDITHelpDoc* CAOIEDITHelpView::GetDocument() const
   { return reinterpret_cast<CAOIEDITHelpDoc*>(m_pDocument); }
#endif

#endif

