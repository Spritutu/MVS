// CPGMianXinTest.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include "CPGDynThreshed1.1.h"
#include "../Inc/MData.h"


using namespace std;

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	//m_ProcessName ="MianXinTestAuto";
	ShowObject=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);

}


void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}

	if(!_stricmp(parm.c_str(),"TEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{

//#ifdef _ENGLISH
//			wstring msg = _T("Set Test Regist Error.Can't read file");
//			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
//#else
//			wstring msg = _T("��ѡ����ʵļ�������ļ�");
//			MessageBox(NULL,msg.c_str(),_T("��ȡ����"),MB_OK);
//#endif
			Hobject  EmptyRegion;
			gen_empty_region(&EmptyRegion);

			m_Parameters.Test_Regist=EmptyRegion;


		}

		string datname = value+".dat";
		if (!_access(datname.c_str(),0))
		{
			TCHAR vv[64];
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),_T("0.0"),vv,sizeof(vv),(s2ws(datname)).c_str());
			StoredModePhi= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterRow= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterColumn= _tstof(vv);

			GetPrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredRadius= _tstof(vv);
		}
	}
		
	if(parm=="BlackMaskSize")
		m_Parameters.BlackMaskSize= atoi(value.c_str());
	if(parm=="BlackPointDynThresh")
		m_Parameters.BlackPointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="BlackPointSize")
		m_Parameters.BlackPointSize= atoi(value.c_str());
	if(parm=="SeriousBlackPointDynThresh")
		m_Parameters.SeriousBlackPointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousBlackPointSize")
		m_Parameters.SeriousBlackPointSize= atoi(value.c_str());


	if(parm=="WhiteMaskSize")
		m_Parameters.WhiteMaskSize= atoi(value.c_str());
	if(parm=="WhitePointDynThresh")
		m_Parameters.WhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhitePointSize")
		m_Parameters.WhitePointSize=atoi(value.c_str());
	if(parm=="SeriousWhitePointDynThresh")
		m_Parameters.SeriousWhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousWhitePointSize")
		m_Parameters.SeriousWhitePointSize=atoi(value.c_str());

	//if(parm=="ZoomRegion")
	//	m_Parameters.ZoomRegion= atoi(value.c_str());

	if(parm=="erosion")
		m_Parameters.erosion= atof(value.c_str());
	if(parm=="ShapeThreshold")
		m_Parameters.ShapeThreshold= atoi(value.c_str());
	if(parm=="ShapeSize")
		m_Parameters.ShapeSize= atoi(value.c_str());


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject LoadRegion;
		HTuple Num;

		Hobject Test_Regist;
		Test_Regist = m_Parameters.Test_Regist;
		//if (m_Parameters.ZoomRegion>0)
		//{
		//	dilation_circle (m_Parameters.Test_Regist, &Test_Regist, m_Parameters.ZoomRegion);
		//}
		//if (m_Parameters.ZoomRegion<0)
		//{
		//	erosion_circle (m_Parameters.Test_Regist, &Test_Regist, -m_Parameters.ZoomRegion);
		//}


		select_shape(Test_Regist, &LoadRegion, "area", "and", 1, 9999999);
		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,200, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDynThreshed1.1 Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGDynThreshed1.1�����ļ���ȡ����");
#endif
			return;
		}

	
		

		Hobject image=pData->m_Image;

		Hlong error_number;

		HTuple    HomMat2DRotate;
		Hobject  RegionAffineTrans,region_tai;
		vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y2, pData->m_center_x2,  pData->m_orientationPhi
			, &HomMat2DRotate);
		affine_trans_region(Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");




		HTuple HomMat2DIdentity,HomMat2DScale;
		HTuple AffineTransArea,AffineTransRow,AffineTransColumn;
		Hobject RegionScaleTrans;


		double Index=pData->r_real/StoredRadius;
		hom_mat2d_identity (&HomMat2DIdentity);

		area_center (RegionAffineTrans, &AffineTransArea, &AffineTransRow, &AffineTransColumn);

		hom_mat2d_scale (HomMat2DIdentity, Index, Index, AffineTransRow, AffineTransColumn, &HomMat2DScale);

		affine_trans_region (RegionAffineTrans, &RegionScaleTrans, HomMat2DScale, "false");


		if (ShowObject&&pData->m_isDebug)
		{
			{
				set_color(pData->m_ShowHWindow,"green");
				disp_obj(RegionScaleTrans,pData->m_ShowHWindow);
			}
		}

		reduce_domain (image, RegionScaleTrans, &region_tai);
		
		
	

		Hobject  BlackImageMean,WhiteImageMean;
		Hobject  BlackPointDynThresh, BLACK_POINT, SeriousBlackPointDynThresh;
		Hobject  SeriousBlackConnected, SERIOUS_BlackPoint;
		Hobject  WhitePointDynThresh, WHITE_POINT, SeriousWhitePointDynThresh;
		Hobject  SeriousWhiteConnected, SERIOUS_WhitePoint;
		Hlong  Number;
		Hobject  Dilation;


			//*===================================================================
		//*�Һ�ɫ�������۵�

		//*��ͼ����о�ֵ������
		//*�������Դ��ڣ�����ʹ����ֵ3��3�����ڸ����׽���ʹ����ֵ9��9��23��23
		//*�������Դ��ף��෴ȡֵ
		//*����֮�����ںڸ����Һ�ʱ������ȶȺܸ���3��3���׸���ڰ׶Աȶȴ�����ܸߵľ�����
		mean_image(region_tai, &BlackImageMean, m_Parameters.BlackMaskSize, m_Parameters.BlackMaskSize);

		//*�һ���
		//*��ɫ���۶�̬��ֵ������ѡȡֵ3.5����
		//dyn_threshold(region_tai, BlackImageMean, &BlackDynThresh, m_Parameters.BlackLineDynThresh, "dark");
		//connection(BlackDynThresh, &BlackConnectedRegions);
		//select_shape(BlackConnectedRegions, &InterestBlackRegion, "area", "and", 5, 99999);
		//count_obj(InterestBlackRegion,&error_number);
		//if (error_number)
		//{
		//	dilation_circle(InterestBlackRegion, &BlackRegionDilation, 3.5);
		//	skeleton(BlackRegionDilation, &BlackSkeleton);

		//	//*���۴�С������8������ֵ���ɸ�����Ҫѡȡ��С���߸��󣬵�ԽС�������ŵĸ���ҲԽ��
		//	select_shape(BlackSkeleton, &BLACK, "area", "and", m_Parameters.BlackLinesLength, 99999);
		//	count_obj(BLACK,&error_number);
		//	if(error_number)
		//	{
		//		//pData->m_ErrorRegist = BLACK;
		//		pData->isFail =true;
		//		testItem->isFailSubTest = true;
		//		//testItem->m_ErrorMsg = "BlackLines error";
		//		//return;
		//		if (pData->isDebug)
		//		{
		//			dilation_circle(BLACK,&Dilation,2.5);
		//			set_color(pData->m_ShowHWindow,"red");
		//			disp_obj(Dilation,pData->m_ShowHWindow);
		//		}
		//	}

		//}
	    
		//*�Ҵ�Χ��ȱ�ݣ�������ȱ��ǳ�Լ������Ƚ϶�����������Խϸ����Խ��
  dyn_threshold(region_tai, BlackImageMean, &BlackPointDynThresh,m_Parameters.BlackPointDynThresh, "dark");
  select_shape(BlackPointDynThresh, &BLACK_POINT, "area", "and", m_Parameters.BlackPointSize, 99999);
  count_obj(BLACK_POINT, &Number);
  if (Number)
  {
	  //pData->m_ErrorRegist = BLACK_POINT;
	  pData->m_isFail =true;
	  testItem->m_bFailSubTest = true;
	  //testItem->m_ErrorMsg = "BlackPoint error";
	  //return;
	  if (pData->m_isDebug)
	  {
		  dilation_circle(BLACK_POINT,&Dilation,2.5);
		  set_color(pData->m_ShowHWindow,"red");
		  disp_obj(Dilation,pData->m_ShowHWindow);
	  }
  }
  //*�ҵ�һ�鼫��ȱ�ݣ��������˵ıȽ���۵�ȽϺڵ����
  dyn_threshold(region_tai, BlackImageMean, &SeriousBlackPointDynThresh,m_Parameters.SeriousBlackPointDynThresh, "dark");
  connection(SeriousBlackPointDynThresh, &SeriousBlackConnected);
  select_shape(SeriousBlackConnected, &SERIOUS_BlackPoint, "area", "and",m_Parameters.SeriousBlackPointSize, 99999);
  count_obj(SERIOUS_BlackPoint, &Number);
  if (Number)
  {
	  //pData->m_ErrorRegist = SERIOUS_BlackPoint;
	  pData->m_isFail =true;
	  testItem->m_bFailSubTest = true;
	  //testItem->m_ErrorMsg = "SeriousBlackPoint error";
	  //return;
	  if (pData->m_isDebug)
	  {
		  dilation_circle(SERIOUS_BlackPoint,&Dilation,2.5);
		  set_color(pData->m_ShowHWindow,"red");
		  disp_obj(Dilation,pData->m_ShowHWindow);
	  }
  }


  		//*===================================================================
		//*�Ұ�ɫ�������۵�

		//*��ͼ����о�ֵ������
		//*�������Դ��ڣ�����ʹ����ֵ9��9��23��23�����ڸ����׽���ʹ����ֵ3��3
		//*�������Դ��ף��෴ȡֵ
		//*����֮�����ڰ׸����Ұ�ʱ������ȶȺܸ���3��3���ڸ���ڰ׶Աȶȴ�����ܸߵľ�����
		//mean_image(region_tai, &WhiteImageMean, m_Parameters.WhiteMaskSize,m_Parameters.WhiteMaskSize);
		////*�һ���

		////*��ɫ���۶�̬��ֵ������ѡȡֵ3.5����
		//dyn_threshold(region_tai, WhiteImageMean, &WhiteDynThresh, m_Parameters.WhiteLineDynThresh, "light");
		//connection(WhiteDynThresh, &WhiteConnectedRegions);

		//select_shape(WhiteConnectedRegions, &InterestWhiteRegion, "area", "and", 5, 99999);
		//count_obj(InterestWhiteRegion,&error_number);
		// if (error_number)
		// {
		//	 dilation_circle(InterestWhiteRegion, &WhiteRegionDilation, 3.5);
		//	 skeleton(WhiteRegionDilation, &WhiteSkeleton);
		//	 //*���۴�С������8������ֵ���ɸ�����Ҫѡȡ��С���߸��󣬵�ԽС�������ŵĸ���ҲԽ��
		//	 select_shape(WhiteSkeleton, &WHITE, "area", "and", m_Parameters.WhiteLinesLength, 99999);
		//	 count_obj(WHITE,&error_number);
		//	 if (error_number)
		//	 {
		//		 //pData->m_ErrorRegist = WHITE;
		//		 pData->isFail =true;
		//		 testItem->isFailSubTest = true;
		//		 //testItem->m_ErrorMsg = "WhiteLines error";
		//		 //return;
		//		 if (pData->isDebug)
		//		 {
		//			 dilation_circle(WHITE,&Dilation,2.5);
		//			 set_color(pData->m_ShowHWindow,"yellow");
		//			 disp_obj(Dilation,pData->m_ShowHWindow);
		//		 }
		//	 }

		// }
  //*===================================================================
  //*�Ұ�ɫ�������۵�
  mean_image(region_tai, &WhiteImageMean, m_Parameters.WhiteMaskSize, m_Parameters.WhiteMaskSize);

  //*�Ҵ�Χ��ȱ��
  dyn_threshold(region_tai, WhiteImageMean, &WhitePointDynThresh, m_Parameters.WhitePointDynThresh, "light");
  select_shape(WhitePointDynThresh, &WHITE_POINT, "area", "and", m_Parameters.WhitePointSize, 99999);
  count_obj(WHITE_POINT, &Number);
  if (Number)
  {
	  //pData->m_ErrorRegist = WHITE_POINT;
	  pData->m_isFail =true;
	  testItem->m_bFailSubTest = true;
	  //testItem->m_ErrorMsg = "WhitePoint error";
	  	  if (pData->m_isDebug)
	  {
		  dilation_circle(WHITE_POINT,&Dilation,2.5);
		  set_color(pData->m_ShowHWindow,"yellow");
		  disp_obj(Dilation,pData->m_ShowHWindow);
	  }
  }
  //*�ҵ�һ�鼫���۵�

  dyn_threshold(region_tai, WhiteImageMean, &SeriousWhitePointDynThresh, m_Parameters.SeriousWhitePointDynThresh, "light");
  connection(SeriousWhitePointDynThresh, &SeriousWhiteConnected);
  select_shape(SeriousWhiteConnected, &SERIOUS_WhitePoint, "area", "and",m_Parameters.SeriousWhitePointSize, 99999);
  count_obj(SERIOUS_WhitePoint, &Number);
  if (Number)
  {
	  //pData->m_ErrorRegist = SERIOUS_WhitePoint;
	  pData->m_isFail =true;
	  testItem->m_bFailSubTest = true;
	  //testItem->m_ErrorMsg = "SeriousWhitePoint error";
	 	  if (pData->m_isDebug)
	  {
		  dilation_circle(SERIOUS_WhitePoint,&Dilation,2.5);
		  set_color(pData->m_ShowHWindow,"yellow");
		  disp_obj(Dilation,pData->m_ShowHWindow);
	  }
  }




		Hobject RegionErosion, ImageReduced2,ModelImages1,ModelRegions1,ConnectedRegions2,SelectedRegions2;

		erosion_circle(RegionScaleTrans, &RegionErosion, m_Parameters.erosion+0.5);
		reduce_domain(image, RegionErosion, &ImageReduced2);
		inspect_shape_model(ImageReduced2, &ModelImages1, &ModelRegions1, 1, m_Parameters.ShapeThreshold);
		connection(ModelRegions1, &ConnectedRegions2);
		select_shape(ConnectedRegions2, &SelectedRegions2, "area", "and", m_Parameters.ShapeSize, 99999);
		


		count_obj(SelectedRegions2,&error_number);
		if (error_number)
		{
			//pData->m_ErrorRegist = SERIOUS_WhitePoint;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "SeriousWhitePoint error";
				  if (pData->m_isDebug)
			{
				dilation_circle(SelectedRegions2,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"blue");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}




		Hobject RegionUnionBlack,RegionUnionWhite,RegionUnionWhole,Union;
		union2(BLACK_POINT, SERIOUS_BlackPoint, &RegionUnionBlack);
		union2(WHITE_POINT, SERIOUS_WhitePoint, &RegionUnionWhite);
		union2(RegionUnionBlack, RegionUnionWhite, &Union);
		union2(Union, SelectedRegions2, &RegionUnionWhole);
		union2(RegionUnionWhole, pData->m_ErrorRegist, &RegionUnionWhole);
		
		//dilation_circle(RegionUnionWhole, &RegionDilation, 2.5);
		pData->m_ErrorRegist=RegionUnionWhole;

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDynThreshed1.1 parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGDynThreshed1.1�������ֵ����,�����µ��ڲ���");
#endif
		
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

}
