
// SLACMVSNDoc.h : CSLACMVSNDoc ��Ľӿ�
//


#pragma once


class CSLACMVSNDoc : public CDocument
{
protected: // �������л�����
	CSLACMVSNDoc();
	DECLARE_DYNCREATE(CSLACMVSNDoc)

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
	virtual ~CSLACMVSNDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


