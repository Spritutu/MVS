#pragma once

#include "tinyxml.h"
#include "afxwin.h"
#include "InspList.h"
#include "GridList_DataModel.h"
// CItemView ��ͼ
#define ItemCNT 43
class CAOIEDITHelpDoc;
class CItemView : public CView
{
	DECLARE_DYNCREATE(CItemView)

protected:
	CItemView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CItemView();
 
public:
	CAOIEDITHelpDoc* GetDocument();
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:
	bool AppOperItem();
	void SaveFile();
	virtual void OnInitialUpdate();
	void OnFileBind(string path);
	void DisplayResult(int nItem,bool bRet);
protected:
	void AddNewItem(TiXmlElement*);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnGridListDbCk(WPARAM wp,LPARAM lp);
	afx_msg LRESULT OnGridListEndEdit(WPARAM wp,LPARAM lp);
	DECLARE_MESSAGE_MAP()
private:
	void InitItemHeader();
	CImageList m_ImageList;
	int        m_nStateImageIdx;
	CInspList m_itemList;
	int m_ItemCollCnt;
	bool m_bIsFileBind;
	TiXmlElement * m_ItemElement;
	bool nItemResFail[ItemCNT];
	char path_buff[MAX_PATH+1];
public:
	afx_msg void OnItemDelete();
	afx_msg void OnItemUp();
	afx_msg void OnItemDown();
};
//#ifndef _DEBUG  // debug version in vw.cpp
//inline CAOIEDITHelpDoc* CItemView::GetDocument()
//{ return (CAOIEDITHelpDoc*) m_pDocument; }
//#endif


