// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// ("Fluent UI")����ʾ������Ϊ�ο������ṩ�� 
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ���� (C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "ChildView.h"
#include "TestTreeView.h"
#include "testlistwnd.h"
#include "PropertiesWnd.h"
#include "TypeCent.h"
#include "..\Inc\TestItemManage.h"
#include "ProgramSettingDlg.h"
#include "LoginDlg.h"
#include <WindowsX.h>
#include "NextFormView.h"
#define  SHOWMessageBox(S) MessageBox(_T(S),_T("ϵͳ��ʾ��"),MB_OK|MB_ICONWARNING)
#define  BTN_MAX 12
#define  ON_WM_RIBBON_HEADER (WM_USER + 102)
const int GroupNum = sizeof(eUSER_GROUP);
class CNextFormView;
class CHomeFormView;
class CMRibbonPage;
class CMConfigCenter;
class CMCtrlCenter;

class CMainFrame : public CFrameWndEx
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)
private:
	volatile eUSER_GROUP m_user;
	bool m_btnEnable[GroupNum][BTN_MAX+1];
public:
	void SetPropertiesWnd(CTlsData *pData)
	{
		__try
		{
			m_wndAlgorithmParameter.SetPropertyList(pData);
		}
		__except(ExpFltr(GetExceptionInformation()))
		{
		}
	};

	void SetTestListWnd(CTlsData *pData){m_wndTestListView.SetTestListWnd(pData);}
	CTestListWnd* GetTestListWndID(){return &m_wndTestListView;};

	void ReflashTestListWnd(int order){m_wndTestListView.ReflashTestListWnd(order);};
	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	void RunInAutoMode();
	void SetUserMode(eUSER_GROUP group);
	void OnMainCtrlInit();

	void ShowErrorLogPic(CMData * pData){m_pNextView->ShowErrorLogPic(pData);};

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CMFCRibbonLabel * m_RibbonLbUser;
protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCRibbonCategory* m_pHomeCategory;
	CMFCRibbonCategory* m_pFilterCategory;
	CMFCRibbonCategory* m_pActiveCategory;
	CMFCToolBarImages   m_PanelImages;
	CMFCToolBarImages   m_PanelImages2;
	CMFCRibbonStatusBar m_wndStatusBar;
	CStatic             m_dispHist;

	CTestTreeView     m_wndFileView;
    CTestListWnd      m_wndTestListView;
	CPropertiesWnd    m_wndAlgorithmParameter;
	CPropertiesWnd    m_wndLightParameter;

	CMFCCaptionBar    m_wndCaptionBar;
	CChildView        m_wndHomeView;

    CMFCRibbonPanel * m_pPanelHistData;

	CMFCRibbonButton* pBtnSaveSYS;
	CMFCRibbonButton* pBtnOpenCfg;
	CMFCRibbonButton* pBtnContinueGrab;

	CMFCRibbonButton* pBtnOPEN;
	CMFCRibbonButton* pBtnCFG;
	CMFCRibbonButton* pBtnRUN;
	CMFCRibbonButton* pBtnSTOP;
	CMFCRibbonButton* pBtnPAUSE;
	CMFCRibbonButton* pBtnSHOT;
	CMRibbonPage   * m_pRibbonPage;
	CMFCRibbonButton* pBtnCONTIN;
	CMFCRibbonButton* pBtnSAVE;
	CMFCRibbonButton* pBtnZERO;
    CHomeFormView   * m_pHomeView;
	CNextFormView   * m_pNextView;
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnViewCaptionBar();
	afx_msg LPARAM OnRibbonCategoryChanged(WPARAM wp, LPARAM lp);
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnCk(CCmdUI* pCmdUI);

	afx_msg LPARAM  OnReciveTLSUpdateMessage(WPARAM wParam, LPARAM lParam);//�������޸���ʵ���������

	afx_msg LRESULT OnRibbonHeaderDraw(WPARAM wp,LPARAM lp);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
#ifdef _ENGLISH
	void InitializeRibbon_English();
#else
	void InitializeRibbon();
#endif
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
	BOOL CreateCaptionBar();
	void GetCmdParameter(CString& strCmd);
public:

	bool CfgDlg();
	bool SelectProgramDlg();
	bool UserDlg();
	bool SysRun();
	bool SysStop();
	bool SysPause();
	bool ShotGrab();
	bool ContinueGrab();
	bool Save();
	bool Zero();
	bool SaveSys();
	bool OpenHelpTool();
	bool HoverOverErrorImages();

	afx_msg void OnBtnClicked(UINT nCmdID);

	bool OneShotGrabErrPic();
    void InitForm();
	//
	LONG ExpFltr(LPEXCEPTION_POINTERS pep);
	void SwitchToForm(UINT nForm);

	BOOL m_bInitPane;
};


