#pragma once
#include "TlsFileParser.h"
#include "afxwin.h"

class CMConfigCenter;
// SaveProgram �Ի���

class SaveProgram : public CDialog
{
	DECLARE_DYNAMIC(SaveProgram)

public:
	SaveProgram(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SaveProgram();


	void AdjustLayout();
	void SetPropertyList();
	void SetPropListFont();

// �Ի�������
	enum { IDD = IDD_DIALOG_SAVEPRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CMFCPropertyGridCtrl m_ProgramList;
	CFont m_fntPropList;

	BOOL OnInitDialog();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT SaveProgram::OnPropertyChanged( WPARAM,LPARAM lParam );

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CStatic m_Static_SaveDLG_ProLogo;
	wstring m_sProgramPath;
	CMConfigCenter* m_pConfigCenter;
};
