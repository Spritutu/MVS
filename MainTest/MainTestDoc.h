
// MainTestDoc.h : CMainTestDoc ��Ľӿ�
//


#pragma once


class CMainTestDoc : public CDocument
{
protected: // �������л�����
	CMainTestDoc();
	DECLARE_DYNCREATE(CMainTestDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMainTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


