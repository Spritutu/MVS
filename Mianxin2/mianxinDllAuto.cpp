// mianxin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "mianxinDllAuto.h"
#include "..\Inc\MData.h"



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	ShowObject=false;
	//m_ProcessName ="MianXinTestAuto";
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


	if(parm=="BlackMaskSize")
		m_Parameters.BlackMaskSize= atoi(value.c_str());
	if(parm=="BlackLineDynThresh")
		m_Parameters.BlackLineDynThresh= ((float)(atof(value.c_str())));
	if(parm=="BlackLinesLength")
		m_Parameters.BlackLinesLength= atoi(value.c_str());
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
	if(parm=="WhiteLineDynThresh")
		m_Parameters.WhiteLineDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhiteLinesLength")
		m_Parameters.WhiteLinesLength= atoi(value.c_str());
	if(parm=="WhitePointDynThresh")
		m_Parameters.WhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhitePointSize")
		m_Parameters.WhitePointSize=atoi(value.c_str());
	if(parm=="SeriousWhitePointDynThresh")
		m_Parameters.SeriousWhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousWhitePointSize")
		m_Parameters.SeriousWhitePointSize=atoi(value.c_str());

	if(parm=="MeanGrayUpperLimit")
		m_Parameters.MeanGrayUpperLimit= atoi(value.c_str());
	if(parm=="MeanGrayLowerLimit")
		m_Parameters.MeanGrayLowerLimit= atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image=pData->m_Image;

		Hobject  ROI,Circle1,Circle2,ContCircle1,ContCircle2,ContCircle;

		if((pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth)>0)
		{
			gen_circle(&Circle1, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));
			//gen_circle_contour_xld (&ContCircle1, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle1, &Circle1, "filled");
			gen_circle(&Circle2, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth));
			//gen_circle_contour_xld (&ContCircle2, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle2, &Circle2, "filled");

			difference(Circle1, Circle2, &ROI);

			if (ShowObject&&pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(Circle1,pData->m_ShowHWindow);
				set_color(pData->m_ShowHWindow,"green");	
				disp_obj(Circle2,pData->m_ShowHWindow);
			}

		}
		else
		{
			gen_circle(&ROI, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));
			//gen_circle_contour_xld (&ContCircle, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle, &ROI, "filled");

			if (ShowObject&&pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(ROI,pData->m_ShowHWindow);
			}
		}



	Hobject  region_tai,Ellipse, ImageReduced, ModelImages;
	Hobject  ModelRegions, ConnectedRegions, SelectedRegions;
	Hobject  Circle, MianXinCircle, BlackImageMean;
	Hobject  BlackDynThresh, BlackConnectedRegions, InterestBlackRegion;
	Hobject  BlackRegionDilation, BlackSkeleton, BLACK, BlackPointDynThresh;
	Hobject  BlackPointConnected, BLACK_POINT, SeriousBlackPointDynThresh;
	Hobject  SeriousBlackPointConnected,SeriousWhitePointConnected;
	Hobject  SERIOUS_BlackPoint, WhiteImageMean, WhiteDynThresh;
	Hobject  WhiteConnectedRegions, InterestWhiteRegion, WhiteRegionDilation;
	Hobject  WhiteSkeleton, WHITE, WhitePointDynThresh, WhitePointConnected;
	Hobject  WHITE_POINT, SeriousWhitePointDynThresh, SERIOUS_WhitePoint;
    Hlong    error_number;
	Hobject  Dilation;
		//*===================================================================
	reduce_domain(image, ROI, &region_tai);
    //*找黑色划痕与污点

    //*对图像进行均值化处理，
    //*若盖面光源打黑，建议使用数值3，3，对于盖面打白建议使用数值9，9至23，23
    //*若盖面光源打白，相反取值
    //*简言之，对于黑盖面找黑时，需均匀度很高用3，3，白盖面黑白对比度大，无需很高的均匀性
    mean_image(region_tai, &BlackImageMean, m_Parameters.BlackMaskSize, m_Parameters.BlackMaskSize);

    //*找划痕
    //*黑色划痕动态阀值，建议选取值3.5以上
    dyn_threshold(region_tai, BlackImageMean, &BlackDynThresh, m_Parameters.BlackLineDynThresh, "dark");
    connection(BlackDynThresh, &BlackConnectedRegions);
    select_shape(BlackConnectedRegions, &InterestBlackRegion, "area", "and", 5, 99999);
	count_obj(InterestBlackRegion,&error_number);
	if (error_number)
	{
		dilation_circle(InterestBlackRegion, &BlackRegionDilation, 3.5);
		skeleton(BlackRegionDilation, &BlackSkeleton);

		//*划痕大小，建议8个像素值，可根据需要选取更小或者更大，但越小发生误排的概率也越大
		select_shape(BlackSkeleton, &BLACK, "area", "and", m_Parameters.BlackLinesLength, 99999);
		count_obj(BLACK,&error_number);
		if(error_number)
		{
			//pData->m_ErrorRegist = BLACK;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "BlackLines error";
			//return;
			if (pData->m_isDebug)
			{
				dilation_circle(BLACK,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}

	}



    //*找黑污点
    //*黑污点动态阀值，建议选取值3.5以上，最好能比黑色划痕动态阀值大，以便清晰的提取点
    dyn_threshold(region_tai, BlackImageMean, &BlackPointDynThresh, m_Parameters.BlackPointDynThresh, "dark");
    connection(BlackPointDynThresh, &BlackPointConnected);
    //*黑污点大小，建议5个像素值以上，可根据需要选取更小或者更大，但越小发生误排的概率也越大
    select_shape(BlackPointConnected, &BLACK_POINT, "area", "and", m_Parameters.BlackPointSize, 99999);
	count_obj(BLACK_POINT,&error_number);
	if(error_number)
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


    //*找极黑污点
    //*极黑污点动态阀值 ,建议选取数值20以上
    dyn_threshold(region_tai, BlackImageMean, &SeriousBlackPointDynThresh, m_Parameters.SeriousBlackPointDynThresh, "dark");
    //*极黑点大小，建议选1开始
	connection(SeriousBlackPointDynThresh, &SeriousBlackPointConnected);
    select_shape(SeriousBlackPointConnected, &SERIOUS_BlackPoint, "area", "and",m_Parameters.SeriousBlackPointSize, 99999);
	count_obj(SERIOUS_BlackPoint,&error_number);
	if(error_number)
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
    //*找白色划痕与污点

    //*对图像进行均值化处理，
    //*若盖面光源打黑，建议使用数值9，9至23，23，对于盖面打白建议使用数值3，3
    //*若盖面光源打白，相反取值
    //*简言之，对于白盖面找白时，需均匀度很高用3，3，黑盖面黑白对比度大，无需很高的均匀性
     mean_image(region_tai, &WhiteImageMean, m_Parameters.WhiteMaskSize,m_Parameters.WhiteMaskSize);
     //*找划痕
 
     //*白色划痕动态阀值，建议选取值3.5以上
     dyn_threshold(region_tai, WhiteImageMean, &WhiteDynThresh, m_Parameters.WhiteLineDynThresh, "light");
     connection(WhiteDynThresh, &WhiteConnectedRegions);
 
     select_shape(WhiteConnectedRegions, &InterestWhiteRegion, "area", "and", 5, 99999);
 	 count_obj(InterestWhiteRegion,&error_number);
	 if (error_number)
	 {
		 dilation_circle(InterestWhiteRegion, &WhiteRegionDilation, 3.5);
		 skeleton(WhiteRegionDilation, &WhiteSkeleton);
		 //*划痕大小，建议8个像素值，可根据需要选取更小或者更大，但越小发生误排的概率也越大
		 select_shape(WhiteSkeleton, &WHITE, "area", "and", m_Parameters.WhiteLinesLength, 99999);
		 count_obj(WHITE,&error_number);
		 if (error_number)
		 {
			 //pData->m_ErrorRegist = WHITE;
			 pData->m_isFail =true;
			 testItem->m_bFailSubTest = true;
			 //testItem->m_ErrorMsg = "WhiteLines error";
			 //return;
			 if (pData->m_isDebug)
			 {
				 dilation_circle(WHITE,&Dilation,2.5);
				 set_color(pData->m_ShowHWindow,"yellow");
				 disp_obj(Dilation,pData->m_ShowHWindow);
			 }
		 }

	 }


	 //*找白污点
	 //*白污点动态阀值，建议选取值3.5以上，最好能比白色划痕动态阀值大，以便清晰的提取点
	 dyn_threshold(region_tai, WhiteImageMean, &WhitePointDynThresh, m_Parameters.WhitePointDynThresh, "light");
	 connection(WhitePointDynThresh, &WhitePointConnected);
     //*白污点大小，建议5个像素值以上，可根据需要选取更小或者更大，但越小发生误排的概率也越大
     select_shape(WhitePointConnected, &WHITE_POINT, "area", "and", m_Parameters.WhitePointSize, 99999);
	 count_obj(WHITE_POINT,&error_number);
	 if (error_number)
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

 
	//*找极白污点

	//*极白污点动态阀值 ,建议选取数值20以上
	dyn_threshold(region_tai, WhiteImageMean, &SeriousWhitePointDynThresh, m_Parameters.SeriousWhitePointDynThresh, "light");
	//*极白点大小，建议选1开始
	connection(SeriousWhitePointDynThresh, &SeriousWhitePointConnected);
	select_shape(SeriousWhitePointConnected, &SERIOUS_WhitePoint, "area", "and", m_Parameters.SeriousWhitePointSize, 99999);
	count_obj(SERIOUS_WhitePoint,&error_number);
	if (error_number)
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

	if (testItem->m_bFailSubTest)
	{
		Hobject RegionUnionBlack,RegionUnionWhite,RegionUnionWhole,Union;
		union2(BLACK,BLACK_POINT,&Union);
		union2(Union, SERIOUS_BlackPoint, &RegionUnionBlack);
		union2(WHITE,WHITE_POINT,&Union);
		union2(Union, SERIOUS_WhitePoint, &RegionUnionWhite);
		union2(RegionUnionBlack, RegionUnionWhite, &RegionUnionWhole);
		//dilation_circle(RegionUnionWhole, &RegionDilation, 2.5);
		union2(pData->m_ErrorRegist, RegionUnionWhole, &RegionUnionWhole);
		pData->m_ErrorRegist=RegionUnionWhole;
	}

    

	//*看表面的平均灰度值. 确定盖子的材质相同
	double Mean,Deviation;
    intensity(ROI, image, &Mean, &Deviation);
	
	if (Mean > m_Parameters.MeanGrayUpperLimit||Mean<m_Parameters.MeanGrayLowerLimit)
	{
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;

		set_color(pData->m_ShowHWindow,"green");
		set_tposition( pData->m_ShowHWindow,25, 145);
		#ifdef _ENGLISH
				write_string(pData->m_ShowHWindow,"mianxinDllAuto Mean Gray	Error");
		#else
				write_string(pData->m_ShowHWindow,"mianxinDllAuto平均灰度异常。请确认参数");
		#endif
		testItem->m_ErrorX = pData->m_center_x;
		testItem->m_ErrorY = pData->m_center_y;
		testItem->m_ErrorR = 8;
		//return;
	}

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"mianxinDllAuto parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"mianxinDllAuto程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

}