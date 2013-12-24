#include "StdAfx.h"
#include "CMData.h"
#include "ActionHalcon.h"
#include "CMCfgCenter.h"

#include "..\..\inc\Tools.h"

namespace AAction
{
	using namespace Halcon;
	namespace Acquirsition
	{
		 char path_buff[MAX_PATH];
		 bool bSizeInit = false;
		 void InitializeRead()
		 {
			 if (!bSizeInit)
			 {
				 bSizeInit = true;
				 char     lpcsType[MAX_STRING];
				 Hlong    lPointer;
				 Hobject m_Image;
				 const char* cz= CMCfgCenter::GetCfgCenter().GetFilePath().c_str();
				 strcpy_s(path_buff,MAX_PATH-1,cz);
				 read_image(&m_Image,path_buff);
				 long width, height;
				 CMCfgCenter::GetCfgCenter().GetImageSize(width, height);
				 Halcon::get_image_pointer1(m_Image,&lPointer,lpcsType,&width,&height);
			 }
		 }
		 void SetPath(string path)
		 {
			 strcpy_s(path_buff,MAX_PATH-1,path.c_str());
		 }
		 inline void acquire(CMData *pData)
		 {
			 read_image(&pData->m_Image,path_buff);
			 pData->m_isDebug=true;
		 }
	};
	namespace INSPECTIONMeasure
	{
		/***  Display window id ***/
		Hlong m_hcDispWindowId=0;
		list<STDoProcess> *m_pDoProcessList;
		typedef list<STDoProcess>::const_iterator CNST_IT;
		SubTestResult testItem ;
		inline void action(CMData * pData)
		{ 
			std::for_each(m_pDoProcessList->begin(), m_pDoProcessList->end(),[&](STDoProcess& processor)
			{
				SubTestResult testResult;
				processor.process(processor.order,pData,&testResult);
				pData->m_vSubTestResult.push_back(testResult);
			});
		}
		void display_close()
		{
		}
		void display_init()
		{
			m_hcDispWindowId = CMCfgCenter::GetCfgCenter().GetHCWnd();
		}
		inline void display(CMData * pData)
		{
			Hlong w,h;
			get_image_size(pData->m_Image,&w,&h);
			//set_part(m_hcDispWindowId,0,0,h-1,w-1);
			disp_obj(pData->m_Image,m_hcDispWindowId);
			
		}
	};
};