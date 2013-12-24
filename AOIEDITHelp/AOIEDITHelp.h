
// AOIEDITHelp.h : AOIEDITHelp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include <string>
// CAOIEDITHelpApp:
// �йش����ʵ�֣������ AOIEDITHelp.cpp
//
#define IDB_FIRST       IDB_QUESTION
#define BMINDEX(x)      (x - IDB_FIRST)
class CMainFrame;
class CAOIEDITHelpDoc;
class CAOIEDITHelpApp : public CWinApp
{
public:
	CAOIEDITHelpApp();

    CImageList    m_images ;
	void LoadBitmaps(BOOL fFree);
	void FreeBitmaps();
public:
	virtual BOOL InitInstance();
    virtual int ExitInstance();
	afx_msg void OnAppAbout();
	afx_msg void OnMyFileOpen();
	DECLARE_MESSAGE_MAP()
public:
	std::wstring m_processID;
	std::wstring m_TLSFileName;
	std::string  m_szTLSFileName;
	std::wstring m_ImageFileName;
	std::wstring m_ProgramName;
	std::wstring m_user;
	CString m_file_path;
    CMainFrame* m_pFrmWnd;
	CAOIEDITHelpDoc * m_currentDocument;
};

extern CAOIEDITHelpApp theApp;
