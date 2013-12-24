#pragma once

#include "TlsFileParser.h"
#include "afxwin.h"
// CProSetRejectTab �Ի���

class CProSetRejectTab : public CPropertyPage
{
	DECLARE_DYNAMIC(CProSetRejectTab)

public:
	CProSetRejectTab();
	virtual ~CProSetRejectTab();

	enum { IDD = IDD_DIALOG_PROSET_REJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:

	BOOL OnInitDialog();

	CButton m_RejectEnable;
	CButton m_RejectTest;
	afx_msg void OnBnClickedButtonTest();
	CEdit m_RejectPort;
	afx_msg void OnBnClickedCheckReject();
	//afx_msg BOOL OnBnClickedOk();
	BOOL OnBnClickedMyOk();
	CEdit m_DelayTime;
	CEdit m_SignelTime;
	// ��������������
	CEdit m_NGCount;
	//��ɫ״ָ̬ʾ��
	CEdit m_RedWinnerPort;
	// //����״ָ̬ʾ��(��ɫ)
	CEdit m_bStatePort;
};
