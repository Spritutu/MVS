
// SLACMVSN.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "SLACMVSN.h"
#include "MainFrm.h"
#include "LoginDlg.h"
#include "SLACMVSNDoc.h"
#include "SLACMVSNView.h"
#include "PanelManager.h"
#include "Splash.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSLACMVSNApp

BEGIN_MESSAGE_MAP(CSLACMVSNApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSLACMVSNApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CSLACMVSNApp ����

CSLACMVSNApp::CSLACMVSNApp()
{
	m_bHiColorIcons = TRUE;
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CSLACMVSNApp ����

CSLACMVSNApp theApp;
MvsConfigurationManager           gConfigManager;
std::vector<PROCESS_INFORMATION>  g_processInfo;
std::vector<HANDLE>               g_processHandle;

// CSLACMVSNApp ��ʼ��

BOOL CSLACMVSNApp::InitInstance()
{
	CString strErrMsg;
	if(!CheckProcess(_T("AOIEDIT.EXE"),strErrMsg))
	{
		AfxMessageBox(strErrMsg);
		exit(-1);
	}
	CWinAppEx::InitInstance();

	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(0);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);
  
	CPanelManager::GetPanelManager().InitAllChannelProcess();
	Sleep(200);
	CPanelManager::GetPanelManager().CreateAllPanels();

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSLACMVSNDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CSLACMVSNView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	m_nCmdShow   =   SW_SHOWMAXIMIZED;   
	if   (!ProcessShellCommand(cmdInfo)) 
		return   FALSE; 
    
	Sleep(300);
    CPanelManager::GetPanelManager().InitAllPanels();
	Sleep(300);
	CPanelManager::GetPanelManager().StartAllPanels();

	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED); 
	m_pMainWnd->UpdateWindow(); 
	return TRUE;
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
// �������жԻ����Ӧ�ó�������
void CSLACMVSNApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
// CSLACMVSNApp �Զ������/���淽��

void CSLACMVSNApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}
void CSLACMVSNApp::LoadCustomState()
{
}
void CSLACMVSNApp::SaveCustomState()
{
}
// CSLACMVSNApp ��Ϣ�������




