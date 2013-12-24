#ifndef  __VISIONDETECT_SDATA__
#define __VISIONDETECT_SDATA__
#include "cpp/HalconCpp.h"
#include "Tool.h"
#include "../../Inc/MData.h"
#define  NUM_BUFFER 5
#define  NUM_RANGE_MAX  500
#define  NUM_RANGE_MIN  0
#define  MSG_REPORT (WM_USER + 102)
struct SData
{	
	Halcon::HRegionArray m_hRegArrCharacters;
	Halcon::HByteImage byte_img;
	Halcon::HImage     himg_img;
	Halcon::Hobject  result_img;  
	Halcon::Hobject  out_Region;  
	Halcon::HTuple   time_needed;  
	Halcon::HTuple   result_handle;
	Halcon::HTuple   decoded_data; 
	Halcon::Hobject  fuzzy_rectangle;
	Halcon::HTuple   fuzzy_RowEdgeFirst,
		             fuzzy_ColumnEdgeFirst,
		             fuzzy_AmplitudeFirst,
		             fuzzy_RowEdgeSecond,
					 fuzzy_ColumnEdgeSecond,
					 fuzzy_AmplitudeSecond,
		             fuzzy_IntraDistance,
					 fuzzy_InterDistance,
	                 fuzzy_Length2,
					 fuzzy_Phi;
};
struct Msg
{
	int process_pos;
	double count_time;
};
typedef struct Msg MsgReport;
extern Hlong g_Image_width;
extern Hlong g_image_height;
extern Hlong g_Fac_HalconWindow;
extern Hlong g_PosX_HalconWindow;
extern Hlong g_PosY_HalconWindow;
#endif