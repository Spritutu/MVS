
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "resource.h"  

#include "..\Inc\TestTreeView.h"

//#include "..\Inc\TestListWnd.h"
#include "..\Inc\TestItemPropertiesWnd.h"
#include "..\Inc\TestItemManage.h"

class CJobMainFrame : public CFrameWndEx
{
	
public: // �������л�����
	CJobMainFrame();
	DECLARE_DYNCREATE(CJobMainFrame)
	std::list<CTlsData*> m_TestList;

// ����
public:

// ����
public:
	

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CJobMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;



	//CTestListWnd        m_wndTestListView;


// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


