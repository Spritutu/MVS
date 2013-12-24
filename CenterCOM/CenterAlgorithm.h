// CenterAlgorithm.h : CCenterAlgorithm ������

#pragma once
#include "resource.h"       // ������
#include <vector>


#include "CenterCOM_i.h"



//#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
//#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� //_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs //�ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
//#endif
using namespace std;
using namespace ATL;


// CCenterAlgorithm

class ATL_NO_VTABLE CCenterAlgorithm :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCenterAlgorithm, &CLSID_CenterAlgorithm>,
	public IDispatchImpl<ICenterAlgorithm, &IID_ICenterAlgorithm, &LIBID_CenterCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CCenterAlgorithm()
	{
		m_vParameters.reserve(4);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CENTERALGORITHM)


BEGIN_COM_MAP(CCenterAlgorithm)
	COM_INTERFACE_ENTRY(ICenterAlgorithm)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		m_vParameters.clear();
	}

	HRESULT STDMETHODCALLTYPE GetAlgorithmName(OLECHAR* algorithmName);
	HRESULT STDMETHODCALLTYPE SetParameter(short* paramIndex, CParameter* pParameter);
	HRESULT STDMETHODCALLTYPE ProcessImageData(CImageData* pImageData, short* parameterIndex, CResult* retResult);
	HRESULT STDMETHODCALLTYPE TrainPrameter(CImageData* pImageData);

private:
	std::vector<CParameter> m_vParameters;
};

OBJECT_ENTRY_AUTO(__uuidof(CenterAlgorithm), CCenterAlgorithm)
