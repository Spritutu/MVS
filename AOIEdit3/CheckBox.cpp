// CheckBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CheckBox.h"


// CCheckBox

IMPLEMENT_DYNAMIC(CCheckBox, CButton)

CCheckBox::CCheckBox()
{

}

CCheckBox::~CCheckBox()
{
}


BEGIN_MESSAGE_MAP(CCheckBox, CButton)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CCheckBox ��Ϣ�������

HBRUSH CCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	//return (HBRUSH)GetStockObject(NULL_BRUSH);
}


void CCheckBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetWindowRect(&rect);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,255,255));
	// ��Ϊ��ͼ��Ϣ���� CButton::OnPaint()
}
