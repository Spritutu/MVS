
// SLACMVSNDoc.cpp : CSLACMVSNDoc ���ʵ��
//

#include "stdafx.h"
#include "SLACMVSN.h"

#include "SLACMVSNDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSLACMVSNDoc

IMPLEMENT_DYNCREATE(CSLACMVSNDoc, CDocument)

BEGIN_MESSAGE_MAP(CSLACMVSNDoc, CDocument)
END_MESSAGE_MAP()


// CSLACMVSNDoc ����/����

CSLACMVSNDoc::CSLACMVSNDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSLACMVSNDoc::~CSLACMVSNDoc()
{
}

BOOL CSLACMVSNDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}




// CSLACMVSNDoc ���л�

void CSLACMVSNDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}


// CSLACMVSNDoc ���

#ifdef _DEBUG
void CSLACMVSNDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSLACMVSNDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSLACMVSNDoc ����
