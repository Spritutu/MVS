// ModalDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "halcon001.h"
#include "ModalDlg.h"


// CModalDlg �Ի���

IMPLEMENT_DYNAMIC(CModalDlg, CDialog)

CModalDlg::CModalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModalDlg::IDD, pParent)
	, sel(0)
{

}

CModalDlg::~CModalDlg()
{
}

void CModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModalDlg, CDialog)
	ON_BN_CLICKED(IDC_CenterHal, &CModalDlg::OnBnClickedCenterhal)
	ON_BN_CLICKED(IDC_CenterC, &CModalDlg::OnBnClickedCenterc)
END_MESSAGE_MAP()


// CModalDlg ��Ϣ�������

void CModalDlg::OnBnClickedCenterhal()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

   *sel=1;
   CModalDlg::OnOK();
}

void CModalDlg::CenterSelectValue(int* CentSel)
{

  sel =CentSel;
    


}

void CModalDlg::OnBnClickedCenterc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	 *sel=2;
	 CModalDlg::OnOK();
}
