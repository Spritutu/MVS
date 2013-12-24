

#ifndef   DLLEXPT
#define DLLEXPT extern "C" __declspec (dllexport )
#endif

#include <string>
using namespace std;
#include "..\Inc\MData.h"

class CDoProcess;

class CParameter
{
	friend CDoProcess;
public:
	CParameter()
	{
		ROIWidth = 3;
		UpperThresholdValue = 18;
		LowerThresholdValue = -18;

		NumPart=300;
		NumNeighbor=3;
		Regional_Out = 0;
		GrayValue = 40;
	};
protected:
public:
	int  ROIWidth;
	double UpperThresholdValue;
	double LowerThresholdValue;
	int  NumPart,NumNeighbor;
	double Regional_Out;
	int GrayValue;
};


class CDoProcess
{

private:
	CParameter m_Parameters;
	int ch;
		bool ShowObject;
public:
	CDoProcess();
	void AutoConfig();
	void SetParmeter(string name,string value);

	void DoProcess(CMData* pData,SubTestResult *testItem);
};


CDoProcess m_Process[MAX_CHANGE_COUNT];

DLLEXPT void AutoConfig()
{
	//printf("AutoConfig");

};

DLLEXPT void SetParameter(int order,string name,string value)
{
	m_Process[order].SetParmeter(name,value);
};

DLLEXPT void SLACDllDoProcess(int order, CMData* pData,SubTestResult *testItem)
{
	m_Process[order].DoProcess(pData,testItem);

};

