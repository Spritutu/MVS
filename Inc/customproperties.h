// This is a part of the Microsoft Foundation Classes C++ library.

// Copyright (c) Microsoft Corporation.  All rights reserved.

//

// This source code is only intended as a supplement to the

// Microsoft Foundation Classes Reference and related

// electronic documentation provided with the library.

// See these sources for detailed information regarding the

// Microsoft Foundation Classes product.


#pragma once
class CCheckBoxProp:public CMFCPropertyGridProperty
{
public:
	CCheckBoxProp(const CString& strName, BOOL bCheck, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
protected:
	virtual BOOL OnEdit(LPPOINT/*lptClick*/) { return FALSE; }
	virtual void OnDrawButton(CDC* /*pDC*/, CRect/*rectButton*/){}
	virtual void OnDrawValue(CDC* /*pDC*/, CRect/*rect*/) {}
	virtual BOOL HasButton() const { return FALSE; }
	virtual BOOL PushChar(UINT nChar);
	virtual void OnDrawCheckBox(CDC * pDC, CRect rectCheck, BOOL bChecked);
	virtual void OnDrawName(CDC* pDC, CRect rect);
	virtual void OnClickName(CPoint point);
	virtual BOOL OnDblClk(CPoint point);
protected:
	CRect m_rectCheck;
};

class CPasswordProp : public CMFCPropertyGridProperty
{
public:
	CPasswordProp(const CString& strName, const CString& strPassword, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
protected:
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual CString FormatProperty();
};

enum VALUE_TYPE{IINT=0,IFLOAT};

class CSliderProp:public CMFCPropertyGridProperty
{
public:
	CSliderProp(const CString& strName, float nValue, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
	CSliderProp(const CString& strName, long nValue, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
	//
	virtual BOOL OnUpdateValue();
	void UpdateValue();
	void SetRang(int min,int max);
	bool GetEndEditFlag()
	{
		return m_bEndEdit;
	}

	void SetEndEditFlag(bool flag)
	{
		m_bEndEdit = flag;
	}

protected:
	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
	virtual BOOL OnSetCursor() const { return FALSE; /* Use default */ }

	CString FormatProperty();
	int m_iMin;
	int m_iMax;
	VALUE_TYPE m_type;
private:
	volatile bool m_bEndEdit;

	int m_nOldPos;
};






class CBoundedNumberPairProp:public CMFCPropertyGridProperty
{
public:
	CBoundedNumberPairProp(const CString& strGroupName, int nMinValue1, int nMaxValue1, int nMinValue2, int nMaxValue2, DWORD _PTRdwData = 0, BOOL bIsValueList = FALSE);
	virtual BOOL OnUpdateValue();
private:
	int m_nMinValue1;
	int m_nMaxValue1;
	int m_nMinValue2;
	int m_nMaxValue2;
};
class CPropertiesWnd;
class CTwoButtonsProp : public CMFCPropertyGridProperty
{
public:
	CTwoButtonsProp(CString& strName, CString& StrValue,CString& helpDescription, CPropertiesWnd * wnd);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void AdjustButtonRect ();
	virtual void OnClickButton (CPoint point);
	virtual void OnDrawButton (CDC* pDC, CRect rectButton);

	CImageList	m_images;
	CPropertiesWnd* m_wnd;
	CString m_pStrName;
	CString m_pStrValue;
};

class CCreateButtonsProp : public CMFCPropertyGridProperty
{
public:
	CCreateButtonsProp(CString& strName, CString& StrValue,CString& helpDescription, CPropertiesWnd * wnd);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void AdjustButtonRect ();
	virtual void OnClickButton (CPoint point);
	virtual void OnDrawButton (CDC* pDC, CRect rectButton);

	CImageList	m_images;
	CPropertiesWnd* m_wnd;
	CString m_pStrName;
	CString m_pStrValue;
};

class CLoadButtonsProp : public CMFCPropertyGridProperty
{
public:
	CLoadButtonsProp(CString& strName, CString& StrValue,CString& helpDescription, CPropertiesWnd * wnd);

protected:
	virtual BOOL HasButton () const	{	return TRUE;	}
	virtual void AdjustButtonRect ();
	virtual void OnClickButton (CPoint point);
	virtual void OnDrawButton (CDC* pDC, CRect rectButton);

	CImageList	m_images;
	CPropertiesWnd* m_wnd;
	CString m_pStrName;
	CString m_pStrValue;
};

class CBoundedNumberSubProp : public CMFCPropertyGridProperty
{
public:
	CBoundedNumberSubProp(const CString& strName, const COleVariant& varValue, int nMinValue, int nMaxValue, LPCTSTR lpszDescr = NULL);
	virtual BOOL OnUpdateValue();
private:
	int m_nMinValue;
	int m_nMaxValue;
};
/////////////////////////////////////////////////////////////////////////////
// CPropSliderCtrl window
class CPropSliderCtrl : public CSliderCtrl
{
	// Construction
public:
	CPropSliderCtrl(CSliderProp* pProp, COLORREF clrBack);

	// Attributes
protected:
	CBrush m_brBackground;
	COLORREF m_clrBack;
	CSliderProp* m_pProp;
	// Implementation
public:
   virtual ~CPropSliderCtrl();
protected:

   //{{AFX_MSG(CPropSliderCtrl)

   afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

   //}}AFX_MSG

   afx_msg void HScroll(UINT nSBCode, UINT nPos);

   DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMReleasedcapture(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

private:
	volatile bool m_bKeyReleased;
	volatile bool m_bKeyHeld;
	volatile bool m_bProcessed;
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

// class CIconListProp : public CMFCPropertyGridProperty
// {
// public:
// 	CIconListProp(const CString& strName, const CImageList& imageListIcons,int nSelectedIcon, CStringList* plstIconNames = NULL, LPCTSTR lpszDescr = NULL, DWORD dwData = 0);
// protected:
// 	virtual CWnd* CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat);
// 	virtual CComboBox* CreateCombo(CWnd* pWndParent, CRect rect);
// 	virtual void OnDrawValue(CDC* pDC, CRect rect);
// 	virtual BOOL OnUpdateValue();
// 	CMFCToolBarImages m_imageListIcons;
// 	CStringList m_lstIconNames;
// };
/////////////////////////////////////////////////////////////////////////////
// CIconCombo window
class CIconCombo : public CComboBox
{
  // Construction
public:
  CIconCombo(CMFCToolBarImages& imageListIcons, CStringList& lstIconNames);
  // Attributes
protected:
  CMFCToolBarImages& m_imageListIcons;
  CStringList& m_lstIconNames;
  // Implementation
public:
  virtual ~CIconCombo();

protected:
  //{{AFX_MSG(CIconCombo)
  afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

  afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);

  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()

};



class CComboBoxExProp : public CMFCPropertyGridProperty
{
public:
   CComboBoxExProp(const CString& strName, const CString& strValue, LPCTSTR lpszDescr = NULL, DWORD dwData = 0, CImageList* pImageList = NULL);
   BOOL AddOption(LPCTSTR lpszOption, int nIcon = -1, int nIndent = 0);
protected:
   virtual CComboBox* CreateCombo(CWnd* pWndParent, CRect rect);
   virtual BOOL OnEdit(LPPOINT lptClick);
   CImageList* m_pImageList;
   CArray<int, int> m_lstIcons;
   CArray<int, int> m_lstIndents;
};

class COwnerDrawDescrProp : public CMFCPropertyGridProperty
{
public:
	COwnerDrawDescrProp(const CString& strName, const COleVariant& varValue);



protected:

   virtual void OnDrawDescription(CDC* pDC, CRect rect);

};







class CCustomDlgProp : public CMFCPropertyGridProperty
{

public:

  CCustomDlgProp(const CString& strName, const COleVariant& varValue);



protected:

  virtual BOOL HasButton() const { return TRUE; }

  virtual void OnClickButton(CPoint point);

};


