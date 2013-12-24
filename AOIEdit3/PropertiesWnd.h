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

#pragma once
#include "..\Inc\TlsFileParser.h"
#include "cpp\HalconCpp.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Halcon;
class CTwoButtonsProp;
class CCreateButtonsProp;
class CLoadButtonsProp;
class CMConfigCenter;
class CMCtrlCenter;

const int LIGHT_PANE     = 0;
const int ALGORITHM_PANE = 1;

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// ����
public:
	CPropertiesWnd(int nPaneType);
	void AdjustLayout();
	void SetPropertyList(CTlsData *pData);
	void SetLightParameters(std::vector<LightCtrlInfo>* pInfos);
    void SetPropListFont();
	void OnClickLeftButton(CString strValue,CTwoButtonsProp* button);
	void OnClickRightButton(CString strValue,CTwoButtonsProp* button);
	void OnClickCreateButton(CString strValue,CCreateButtonsProp* button);
	void OnClickLoadButton(CString strValue,CLoadButtonsProp* button);
// ����
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
protected:
	CFont m_fntPropList;
	CPropertiesToolBar   m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;
	CTlsData* m_CurrentData;
	std::vector<LightCtrlInfo>* m_pLightCtrlParam;

	Hobject m_Region;
private:
	void InitPropList();
// ʵ��
public:
	virtual ~CPropertiesWnd();
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnAddTestList();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged( WPARAM,LPARAM lParam );
	DECLARE_MESSAGE_MAP()
	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  LastTime;
	__int64  nowTime;

private:
	CMConfigCenter* m_pConfigCenter;
    CMCtrlCenter* m_pCtrlCenter;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual HRESULT get_accSelection(VARIANT *pvarChildren);
	void EnableEditTestName(BOOL flag);
private:
	int m_nPaneType; // use this flag to indicate if this pane is a Light Controller Pane or Algorithm Parameter Pane
	                // 0 : Light Parameter Pane;
	                // 1 : Algorithm Parameter Pane;
	void OnLightParamPanePropertyChanged(LPARAM lParam);
	void OnAlgorithmParamPanePropertyChanged(LPARAM lParam);

	CMFCPropertyGridProperty* m_pTestNamePro;
	CMFCPropertyGridProperty* m_pSubtestNamePro;
};

