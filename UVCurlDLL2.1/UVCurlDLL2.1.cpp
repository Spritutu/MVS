// CanCurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "UVCurlDll2.1.h"
#include "\slacmvs\trunk\Inc\MData.h"

#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;
}

CDoProcess::CDoProcess()
{
	ShowObject=false;
	//m_ProcessName ="QinanHuanTest";
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
	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());
	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());
	if(parm=="DriftAngle1")
		m_Parameters.DriftAngle1 = atof(value.c_str());
	if(parm=="DriftAngle2")
		m_Parameters.DriftAngle2 = atof(value.c_str());
	if(parm=="NumPart")
		m_Parameters.NumPart = atoi(value.c_str());
	if(parm=="ThresholdValue")
		m_Parameters.ThresholdValue = atof(value.c_str());
	if(parm=="GrayValue")
		m_Parameters.GrayValue = atoi(value.c_str());
	if(parm=="MeanGray")
		m_Parameters.MeanGray = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image = pData->m_Image;
		double ThresholdValue;

		int  GrayValue;

		int  NumPart;

		NumPart = m_Parameters.NumPart;

		ThresholdValue = m_Parameters.ThresholdValue;

		GrayValue =m_Parameters.GrayValue;

		double Regional_Out;

		Regional_Out =pData->r_real+m_Parameters.Regional_Out;

		Hlong error_number; 
		error_number = 0;

		  Hobject  PolarTransImage,ImageScaleMax, JuanYuanPartitioned, ResultDefect;
		  Hobject  BackTransRegion,Circle1,Circle2,Circle,Rectangle1,ROI;

		  // Local control variables 
		  HTuple  Pointer, Type, WidthOri, HeightOri;
		  HTuple  PolarTransImageWidth, PolarTransImageHeight;
		  HTuple  Mean, Deviation, Mean_Lenght, Mean_deviation;
		  HTuple  i, Exp, Abs, AbsSorted, LocationId, Length;
		  HTuple  ResultID,MeanSorted;
		  HTuple  LocationId2, Length1, ResultID2, ResultID3;
		  HTuple  Sorted, Uniq,errorValue;
          double  TempCenterRow,TempCenterColumn,TempCenterRadius;
		  double  m_orientationPhi;

		get_image_pointer1(image, &Pointer, &Type, &WidthOri, &HeightOri);

		//if (ShowObject&&pData->m_isDebug)
		//{
		//	gen_circle(&Circle, (pData->Center_y2), (pData->Center_x2), (m_Parameters.PartitionBoundary));
		//	set_color(pData->m_ShowHWindow,"orange");	
		//	disp_obj(Circle,pData->m_ShowHWindow);

		//}

		//if (0 != (Regional_Out>m_Parameters.PartitionBoundary))
		//{
			TempCenterRow = pData->m_center_y;
			TempCenterColumn = pData->m_center_x;
			TempCenterRadius = pData->r_real;
		
		//}
		//else
		//{
		//	TempCenterRow = pData->Center_y2;
		//	TempCenterColumn = pData->Center_x2;
		//	TempCenterRadius = pData->r_real2;
		//
		//}

	//*==================================================================================================	
		m_orientationPhi = (HTuple(180).Rad()[0].D())+pData->m_orientationPhi;

		if (ShowObject&&pData->m_isDebug)
		{
			if (0 != (m_Parameters.DriftAngle1==m_Parameters.DriftAngle2))
			{
				set_color(pData->m_ShowHWindow,"green");
				set_tposition( pData->m_ShowHWindow,5, 145);
				#ifdef _ENGLISH
								write_string(pData->m_ShowHWindow,"Drift angle values are the ​​same, please re-adjust the parameters");
				#else
								write_string(pData->m_ShowHWindow,"偏移角度相同,请重新调节偏移角度");
				#endif
				return;
			}
		}

		//*======================================================================================================
		//*测外圈卷边
		gen_rectangle1(&Rectangle1, 0, 0, m_Parameters.ROIWidth, WidthOri);
		polar_trans_region_inv(Rectangle1, &ROI, TempCenterRow, TempCenterColumn, 
			m_orientationPhi+(m_Parameters.DriftAngle1.Rad()), m_orientationPhi+(m_Parameters.DriftAngle2.Rad()), Regional_Out, 
			Regional_Out-m_Parameters.ROIWidth, WidthOri, m_Parameters.ROIWidth, WidthOri, HeightOri, "nearest_neighbor");

		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"blue");	
			disp_obj(ROI,pData->m_ShowHWindow);
		}
  //*===================================================================
		polar_trans_image_ext(image, &PolarTransImage, TempCenterRow, TempCenterColumn, 
		m_orientationPhi+(m_Parameters.DriftAngle1.Rad()), m_orientationPhi+(m_Parameters.DriftAngle2.Rad()), Regional_Out, 
		Regional_Out-m_Parameters.ROIWidth, WidthOri, m_Parameters.ROIWidth, "nearest_neighbor");
		get_image_size(PolarTransImage, &PolarTransImageWidth, &PolarTransImageHeight);

		scale_image_max(PolarTransImage, &ImageScaleMax);
		partition_rectangle(ImageScaleMax, &JuanYuanPartitioned, PolarTransImageWidth/NumPart, 
			PolarTransImageHeight);

		intensity(JuanYuanPartitioned, ImageScaleMax, &Mean, &Deviation);

		tuple_length(Mean, &Mean_Lenght);
		Mean_deviation = HTuple();
		for (i=0; i<=Mean_Lenght-2; i+=1)
		{
		  tuple_deviation(HTuple(Mean[i]).Concat(HTuple(Mean[i+1])), &Exp);
		  Mean_deviation[i] = Exp;
		}

		tuple_abs(Mean_deviation, &Abs);
		tuple_sort(Abs, &AbsSorted);
		tuple_sort_index(Abs, &LocationId);
		tuple_length(Abs, &Length);

		errorValue = AbsSorted[Length-1];
		for (i=Length-1; i>=0; i+=-1)
		{
		  if (0 != (HTuple(AbsSorted[i])<ThresholdValue))
		  {
			//  errorValue = AbsSorted[i];
			if (0 != (i==(Length-1)))
			{
			  ResultID = HTuple();
			  break;
			}
			else
			{
			  tuple_last_n(LocationId, i+1, &ResultID);
			  break;
			}
		  }
		}

		ResultID += 1;


		tuple_sort(Mean, &MeanSorted);
		tuple_sort_index(Mean, &LocationId2);
		tuple_length(Mean, &Length1);

		ResultID2 = HTuple();
		for (i=0; i<=Length1-1; i+=1)
		{

			if (0 != (HTuple(MeanSorted[i])<GrayValue))
			{

				ResultID2[i] = HTuple(LocationId2[i]);

			}
			else
			{
				break;

			}
		}


		ResultID2 += 1;

		tuple_concat(ResultID, ResultID2, &ResultID3);

		tuple_sort(ResultID3, &Sorted);

		tuple_uniq(Sorted, &Uniq);


		select_obj(JuanYuanPartitioned, &ResultDefect, Uniq);


		polar_trans_region_inv(ResultDefect, &BackTransRegion, TempCenterRow, TempCenterColumn, 
			m_orientationPhi+(m_Parameters.DriftAngle1.Rad()), m_orientationPhi+(m_Parameters.DriftAngle2.Rad()), Regional_Out, 
			Regional_Out-m_Parameters.ROIWidth, WidthOri, m_Parameters.ROIWidth, WidthOri, HeightOri, "nearest_neighbor");


		count_obj(BackTransRegion,&error_number);
		
		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			//Hlong Area;
			//double yy,xx;
			//area_center(BackTransRegion,&Area,&yy,&xx);
			//testItem->m_ErrorY = yy;
			//testItem->m_ErrorX = xx;
			//char msg[MAX_PATH];
			//sprintf_s(msg,sizeof(msg),"UV Curl Out Error, current_thred=%f,  set_thred=%f",errorValue[0].D(),ThresholdValue);
			//testItem->m_ErrorMsg = msg;

			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"yellow");
				disp_obj(BackTransRegion,pData->m_ShowHWindow);
			}

			Hobject RegionUnionWhole;
			union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);

			pData->m_ErrorRegist=RegionUnionWhole;	
		}


		Hobject MianXinDomain;
		change_domain(image, ROI, &MianXinDomain);
		HTuple  Mean1, Deviation1;

		intensity(ROI, MianXinDomain, &Mean1, &Deviation1);


		if (Mean1<m_Parameters.MeanGray)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");	
				disp_obj(ROI,pData->m_ShowHWindow);
				set_tposition( pData->m_ShowHWindow,120, 0);
				#ifdef _ENGLISH
								write_string(pData->m_ShowHWindow,"Out of compound");
				#else
								write_string(pData->m_ShowHWindow,"有大量区域未补涂");
				#endif
			}

			Hobject RegionUnionWhole;
			union2(BackTransRegion,ROI,&RegionUnionWhole);
			union2(RegionUnionWhole,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;

		}
	

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"UVCurlDll2.1 parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"UVCurlDll2.1程序参数值出错,请重新调节参数");
			#endif

		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }
