/*#define TIXML_USE_STL*/

#include "stdafx.h"
#include "..\Inc\tinxml\tinyxml.h"
#include "stdio.h"
#include "Tools.h"
#include "TlsFileParser.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"
#include "../AOIEdit3/AOIEditVer3.h"

#include <atlconv.h>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

#pragma region class CTlsData methods
STLSDATA_SUBTEST* CTlsData::GetDataSubtest()
{
	if(m_data.type==NONE)
	{
		m_data.data.pDataSubtest = new STLSDATA_SUBTEST();
		size_t sz = sizeof(STLSDATA_SUBTEST);
		m_data.type=SUBTEST;
	}
	ASSERT(m_data.type==SUBTEST);
	return m_data.data.pDataSubtest;
}

STLSDATA_TEST* CTlsData::GetDataTest()
{
	if(m_data.type==NONE)
	{
		m_data.data.pDataTest = new STLSDATA_TEST();
		m_data.type = TEST;
	}
	ASSERT(m_data.type==TEST);
	return m_data.data.pDataTest;
}

STLSDATA_COMMON* CTlsData::GetDataCommon()
{
	if(m_data.type==NONE)
	{	
		m_data.data.pDataCommon = new STLSDATA_COMMON();
		m_data.type = COMMON;
	}
	ASSERT(m_data.type==COMMON);
	return m_data.data.pDataCommon;
}

CTlsData::~CTlsData()
{
}

#pragma endregion class CTlsData methods

#pragma region class TlsFileParser member

TlsFileParser::TlsFileParser()
{

}
TlsFileParser::~TlsFileParser()
{
	ReleaseMem();
}
void TlsFileParser::ReleaseMem()
{
	m_vTestData.clear();
}
void TlsFileParser::SaveTLS(string fileName)
{
	m_Doc.SaveFile(fileName.c_str());
}

int TlsFileParser::Init(const char *filename)
{	
	ReleaseMem();
	if (!m_Doc.LoadFile(filename))
	{
		wstring wstrErr = s2ws(string(m_Doc.ErrorDesc()));
		CString cstrErr(_T("Cannot load MAS file!"));
		cstrErr.AppendFormat(_T("%s"),wstrErr.c_str());
		AfxMessageBox(cstrErr,MB_OK|MB_ICONWARNING);
		return 1;
	}
	m_pRootElement = m_Doc.RootElement();
	if ((m_pRootElement == nullptr) || 0 != strcmp((m_pRootElement->Value()),"slactls"))
	{
		AfxMessageBox(_T("Cannot find slactls"),MB_OK|MB_ICONWARNING);
		return 1;
	}
	mTestInstanceElement = m_pRootElement->FirstChildElement("test_instance");
	if ((mTestInstanceElement == nullptr))
	{
		AfxMessageBox(_T("TLS file is invalid!"),MB_OK|MB_ICONWARNING);
		return 1;
	}
	if (SetCommonInfo())
	{
		return 1;
	}
	if (SetTestList())
	{
		return 1;
	}
	return 0;
}

int TlsFileParser::SetCommonInfo()
{
	m_pCommonElement = m_pRootElement->FirstChildElement("common");
	if (!m_pCommonElement)
	{
		return 1;
	}
	CTlsData data;
	STLSDATA_COMMON* pCommon = data.GetDataCommon();
	pCommon->commname = "Common";
	for (TiXmlNode *node = m_pCommonElement->FirstChildElement();node;node = node->NextSiblingElement())
	{
		string name = node->Value();
		string value = node->FirstChild()->Value();
		pCommon->property_.insert(make_pair(name,value));
	}
	m_vTestData.push_back(data);
	return 0;
}

int TlsFileParser::SetTestList()
{
	TiXmlElement *testLoopElement,*subTestLoopElement;
	TiXmlElement *exeElement;
	TiXmlElement *parameterLoopElement,*propertyElement;
	TiXmlNode *node;
	for (testLoopElement = mTestInstanceElement->FirstChildElement("test"); testLoopElement;testLoopElement = testLoopElement->NextSiblingElement("test") )
	{
		CTlsData data;
		STLSDATA_TEST* pTest = data.GetDataTest();
		pTest->testName = testLoopElement->FirstAttribute()->Value();
		pTest->helpDesc = testLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();
		propertyElement = testLoopElement->FirstChildElement("property"); 
		for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
		{
			string name = node->Value();
			string value = node->FirstChild()->Value();
			pTest->property_.insert(map<string,string>::value_type(name,value));

		}
		m_vTestData.push_back(data);
		int order = 0;
		for (subTestLoopElement = testLoopElement->FirstChildElement("subtest"); subTestLoopElement;subTestLoopElement = subTestLoopElement->NextSiblingElement("subtest") )
		{
			CTlsData SubTestData;
			STLSDATA_SUBTEST* pSubTest = SubTestData.GetDataSubtest();
			pSubTest->m_strSubTestName = subTestLoopElement->FirstAttribute()->Value();			
			pSubTest->testName = pTest->testName;
			pSubTest->helpDesc = subTestLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();
			
			pSubTest->order = order++;
			pSubTest->RunTest = subTestLoopElement->FirstChildElement("runtest")->FirstChild()->Value();
			exeElement = subTestLoopElement->FirstChildElement("exe");
			if (exeElement == nullptr)
			{
				errorMsg = "Cannot Find exe. file!";
				return -1;
			}
			node =exeElement->FirstChildElement("exename");
			if (node == nullptr)
			{
				errorMsg = "Cannot Find exename.";
				return -1;
			}
			pSubTest->exeName = node->FirstChild()->Value();

			node = exeElement->FirstChildElement("exeversion");	
			if (node == nullptr)
			{
				errorMsg = "Cannot Find exeversion.";
				return -1;
			}
			pSubTest->exeVersion = node->FirstChild()->Value();

			for (parameterLoopElement = subTestLoopElement->FirstChildElement("parameter"); parameterLoopElement;parameterLoopElement = parameterLoopElement->NextSiblingElement("parameter"))
			{
				STLSDATA_PARAMETER parameter;

				const char* des = parameterLoopElement->Attribute("parameterDesc");
				if (des)
				{
					parameter.parameterDesc = string(des);
				}
				parameter.parameterName = parameterLoopElement->FirstAttribute()->Value();
				parameter.settingValue = parameterLoopElement->FirstChildElement("setting")->FirstChild()->Value();
				parameter.helpDesc = parameterLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();
				propertyElement = parameterLoopElement->FirstChildElement("property"); 
				for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
				{
					string name = node->Value();
					if (name=="listvalue")
					{
						continue;
					}
					string value = node->FirstChild()->Value();
					parameter.property_.insert(map<string,string>::value_type(name,value));
					if(!_stricmp(node->FirstChild()->Value(),"ilist"))
					{
						TiXmlNode *ListValueNode;
						TiXmlElement * listvalueyElement = propertyElement->FirstChildElement("listvalue"); 
						parameter.valueList.clear();
						for (ListValueNode = listvalueyElement->FirstChildElement();ListValueNode;ListValueNode = ListValueNode->NextSiblingElement())
						{
							string name = ListValueNode->Value();
							parameter.valueList.push_back(name);
						}
					}		
				}
				pSubTest->m_vParameters.push_back(parameter);
			}

			propertyElement = subTestLoopElement->FirstChildElement("property"); 
			for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
			{
				string name = node->Value();
				string value = node->FirstChild()->Value();
				pSubTest->property_.insert(map<string,string>::value_type(name,value));

			}
			m_vTestData.push_back(SubTestData);
		}
	}
	return 0;
}


#pragma endregion class TlsFileParser member

#pragma region class CTestItemList methods

bool CTestItemList::OpenTLS(string fileName)
{
	bool loadOkay = m_Doc.LoadFile(fileName.c_str());
	if ( !loadOkay)
	{
		cout<<"Cannot load test file 'demotest.xml'. Error= "<<m_Doc.ErrorDesc()<<". Exiting."<<endl;
		return 1;
	}
	m_pRootElement = m_Doc.RootElement();
	if ((m_pRootElement ==NULL) || strcmp((m_pRootElement->Value()),"test_instance"))
	{
		cout<<"Cannot find test_instance"<<endl;
		return 1;
	}

	TiXmlElement *testLoopElement,*subTestLoopElement;
	TiXmlElement *exeElement;
	TiXmlElement *parameterLoopElement,*propertyElement;
	TiXmlNode *node;
	int order = 0;
	for (testLoopElement = m_pRootElement->FirstChildElement("test"); testLoopElement;testLoopElement = testLoopElement->NextSiblingElement("test") )
	{
		for (subTestLoopElement = testLoopElement->FirstChildElement("subtest"); subTestLoopElement;subTestLoopElement = subTestLoopElement->NextSiblingElement("subtest") )
		{
			CTlsData data;
			STLSDATA_SUBTEST* pSubTest = data.GetDataSubtest();

			pSubTest->m_strSubTestName = subTestLoopElement->FirstAttribute()->Value();			
			pSubTest->testName = testLoopElement->FirstAttribute()->Value();

			pSubTest->helpDesc = subTestLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();
			pSubTest->order = atoi(subTestLoopElement->FirstChildElement("order")->FirstChild()->Value());
			pSubTest->order = order++;
			pSubTest->RunTest = subTestLoopElement->FirstChildElement("runtest")->FirstChild()->Value();

			exeElement = subTestLoopElement->FirstChildElement("exe");
			if (exeElement == nullptr)
			{
				return false;
			}
			node =exeElement->FirstChildElement("exename");
			if (node == nullptr)
			{
				return false;
			}
			pSubTest->exeName = node->FirstChild()->Value();
			node = exeElement->FirstChildElement("exeversion");	
			if (node == nullptr)
			{
				return false;
			}
			pSubTest->exeVersion = node->FirstChild()->Value();

			for (parameterLoopElement = subTestLoopElement->FirstChildElement("parameter"); parameterLoopElement;parameterLoopElement = parameterLoopElement->NextSiblingElement("parameter"))
			{
				STLSDATA_PARAMETER parameter ;
				parameter.parameterName = parameterLoopElement->FirstAttribute()->Value();

				const char* des = parameterLoopElement->Attribute("parameterDesc");
				if (des)
				{
					parameter.parameterDesc = des;
				}

				parameter.settingValue = parameterLoopElement->FirstChildElement("setting")->FirstChild()->Value();
				parameter.helpDesc = parameterLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();

				propertyElement = parameterLoopElement->FirstChildElement("property"); 
				for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
				{
					string name = node->Value();
					if (name=="listvalue")
					{
						continue;
					}
					string value = node->FirstChild()->Value();
					parameter.property_.insert(map<string,string>::value_type(name,value));
					if(!_stricmp(node->FirstChild()->Value(),"ilist"))
					{
						TiXmlNode *ListValueNode;
						TiXmlElement * listvalueyElement = propertyElement->FirstChildElement("listvalue"); 
						parameter.valueList.clear();
						for (ListValueNode = listvalueyElement->FirstChildElement();ListValueNode;ListValueNode = ListValueNode->NextSiblingElement())
						{
							string name = ListValueNode->Value();
							parameter.valueList.push_back(name);
						}
					}		
				}
				pSubTest->m_vParameters.push_back(parameter);
			}

			propertyElement = subTestLoopElement->FirstChildElement("property"); 
			for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
			{
				string name = node->Value();
				string value = node->FirstChild()->Value();
				pSubTest->property_.insert(map<string,string>::value_type(name,value));
			}
			m_lTestList->push_back(data);
		}
	}
	return true;
}

void CTestItemList::SaveTLS(string fileName)
{
	TiXmlDocument xmlDoc(fileName.c_str());
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0","gb2312", "yes" ); // 声明XML的属性
	xmlDoc.LinkEndChild( decl ); 

	TiXmlElement* pRootElm = new TiXmlElement( "test_instance" );
	TiXmlElement * pNode = NULL; 
	xmlDoc.LinkEndChild(pRootElm) ;

	TiXmlComment * comment = new TiXmlComment();
	comment->SetValue(" Settings for MyApp " ); 
	pRootElm->LinkEndChild( comment ); 
	// Sort the test by its order
	std::vector<CTlsData> tmpTest;
	tmpTest.assign(m_lTestList->begin(), m_lTestList->end());
	std::sort(tmpTest.begin(), tmpTest.end(), [](CTlsData& l, CTlsData& r)->bool
	{
		STLSDATA_SUBTEST* pL = l.GetDataSubtest();
		STLSDATA_SUBTEST* pR = r.GetDataSubtest();
		return pL->order < pR->order;
	});
	m_lTestList->clear();
	m_lTestList->assign(tmpTest.begin(), tmpTest.end());
	
	for (auto it = m_lTestList->begin(); it != m_lTestList->end();it++)
	{
		STLSDATA_SUBTEST* pSubTest = (*it).GetDataSubtest();

		TiXmlElement * pTestItem = new TiXmlElement( "test");
		pTestItem->SetAttribute("testid", pSubTest->testName.c_str());
		pRootElm->LinkEndChild( pTestItem ); 

		TiXmlElement * pSubTestItem = new TiXmlElement( "subtest"); 
		pSubTestItem->SetAttribute("subtestid", pSubTest->m_strSubTestName.c_str());
		pTestItem->LinkEndChild( pSubTestItem ); 

		TiXmlElement * pExe = new TiXmlElement( "exe"); 
		pSubTestItem->LinkEndChild( pExe ); 
		pNode = new TiXmlElement( "exename" ); 
		pNode->LinkEndChild( new TiXmlText( pSubTest->exeName.c_str() )); 
		pExe->LinkEndChild( pNode ); 
		pNode = new TiXmlElement( "exeversion" ); 
		pNode->LinkEndChild( new TiXmlText( pSubTest->exeVersion.c_str() )); 
		pExe->LinkEndChild( pNode ); 

		auto parameter = pSubTest->m_vParameters;

		for (auto parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
		{
			TiXmlElement* parameter = new TiXmlElement( "parameter" ); 
			parameter->SetAttribute("name", (*parameterIt).parameterName.c_str());
			parameter->SetAttribute("parameterDesc", (*parameterIt).parameterDesc.c_str());

			TiXmlElement* ParamProperty = new TiXmlElement( "property" ); 
			parameter->LinkEndChild(ParamProperty);
			Property *ParamPropertyMap = &((*parameterIt).property_);
			for (auto propertyIt = ParamPropertyMap->begin();propertyIt!=ParamPropertyMap->end();propertyIt++)
			{
				pNode = new TiXmlElement( propertyIt->first.c_str()); 
				pNode->LinkEndChild( new TiXmlText(propertyIt->second.c_str())); 
				ParamProperty->LinkEndChild( pNode );
				if(!_stricmp(propertyIt->second.c_str(),"ilist"))
				{
					TiXmlElement* ParamPropertyListValue = new TiXmlElement( "listvalue" );
					for (auto listValueIt=(*parameterIt).valueList.begin();listValueIt!=(*parameterIt).valueList.end();listValueIt++)
					{
						pNode = new TiXmlElement( (*listValueIt).c_str()); 
						ParamPropertyListValue->LinkEndChild( pNode );
					}
					ParamProperty->LinkEndChild(ParamPropertyListValue);
				}
			}
			pNode = new TiXmlElement( "setting" ); 
			pNode->LinkEndChild( new TiXmlText((*parameterIt).settingValue.c_str())); 
			parameter->LinkEndChild( pNode );

			pNode = new TiXmlElement( "helpdescription" ); 
			pNode->LinkEndChild( new TiXmlText((*parameterIt).helpDesc.c_str())); 
			parameter->LinkEndChild( pNode );
			pSubTestItem->LinkEndChild(parameter);
		}

		TiXmlElement* subTestProperty = new TiXmlElement( "property" ); 
		pSubTestItem->LinkEndChild(subTestProperty);
		Property *subTestPropertyMap = &(pSubTest->property_);
		for (auto propertyIt=subTestPropertyMap->begin();propertyIt!=subTestPropertyMap->end();propertyIt++)
		{
			pNode = new TiXmlElement( propertyIt->first.c_str()); 
			pNode->LinkEndChild( new TiXmlText(propertyIt->second.c_str())); 
			subTestProperty->LinkEndChild( pNode );
		}
		pNode = new TiXmlElement( "order" ); 
		char order[32];
		memset(order,0,sizeof(order));

		_itoa_s(pSubTest->order,order,10);

		pNode->LinkEndChild( new TiXmlText( order)); 
		pSubTestItem->LinkEndChild( pNode );

		pNode = new TiXmlElement( "runtest" ); 
		pNode->LinkEndChild( new TiXmlText( pSubTest->RunTest.c_str())); 
		pSubTestItem->LinkEndChild( pNode );

		pNode = new TiXmlElement( "helpdescription" ); 
		pNode->LinkEndChild( new TiXmlText( pSubTest->helpDesc.c_str())); 
		pSubTestItem->LinkEndChild( pNode );
	}
	xmlDoc.Print() ;
	xmlDoc.SaveFile(); // 把XML文件写入硬盘		
}

void CTestItemList::SetTestList(std::vector<CTlsData>* lTestList)
{
	m_lTestList = lTestList;
}

#pragma endregion class CTestItemList methods

ProgramData::ProgramData()
	:m_bSaveERRImage(false),
	 m_bConnect2LightCtrl(false),
	 m_bSavePassImage(false)
{
	m_eSource = NONE_SOURCE;
	m_sProgramName="NULL";
	m_sTLSFileName="NULL";
	m_CameraInfo.m_triggerEdge = RISING_EDGE;
	m_sFilePath="NULL";
	m_sFileName="NULL";
	m_vLightCtrlInfo.clear();
}

ProgramData::~ProgramData()
{
}

void ProgramData::LoadCameraAndLightSetting(TiXmlElement* pRootElement)
{
	TiXmlElement* CameraElement = pRootElement->FirstChildElement("CameraSetting");
	if (CameraElement!=NULL)
	{
		TiXmlNode* node = CameraElement->FirstChildElement("CameraName");
		m_CameraInfo.m_sCameraName  = node->FirstChild()->Value();

		node = CameraElement->FirstChildElement("TriggerMode");
		if(node != nullptr && !_stricmp(node->FirstChild()->Value(),"YES"))
			m_CameraInfo.m_bTriggerMode = true;
		else
			m_CameraInfo.m_bTriggerMode = false;

		node = CameraElement->FirstChildElement("TriggerActivation");
		if(node != nullptr && !_stricmp(node->FirstChild()->Value(),"RisingEdge"))
			m_CameraInfo.m_triggerEdge = RISING_EDGE;
		else
			m_CameraInfo.m_triggerEdge = FALLING_EDGE;

		node = CameraElement->FirstChildElement("CameraGain");
		if (node!= nullptr)
			m_CameraInfo.m_gain  = atoi(node->FirstChild()->Value());
		else
			m_CameraInfo.m_gain = 0;

		node = CameraElement->FirstChildElement("TriggerDelayAbs");
		if (node!= nullptr)
			m_CameraInfo.m_triggerDelayAbs  = atoi(node->FirstChild()->Value());
		else
			m_CameraInfo.m_triggerDelayAbs = 0;

		node = CameraElement->FirstChildElement("LinesPerFrame");
		if(node != nullptr)
		{
			m_CameraInfo.m_linesPerFrame =  atoi(node->FirstChild()->Value());
		}

		node = CameraElement->FirstChildElement("FramesPerSheet");
		if(node != nullptr)
		{
			m_CameraInfo.m_framesPerSheet =  atoi(node->FirstChild()->Value());
		}

		node = CameraElement->FirstChildElement("Connect2LightCtrlFlag");
		CMConfigCenter::GetSingletonConfigCenter()->SetConnect2LightCtrlFlag(false);
		if(node != nullptr && !_stricmp(node->FirstChild()->Value(),"YES"))
		{
			CMConfigCenter::GetSingletonConfigCenter()->SetConnect2LightCtrlFlag(true);
		}
	}
}

void ProgramData::LoadRejectUnitSetting(TiXmlElement* pRootElement)
{
	TiXmlElement* RejectElement = pRootElement->FirstChildElement("RejectSetting");
	if (RejectElement != nullptr)
	{
		auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
		string value;
		TiXmlNode* node = RejectElement->FirstChildElement("port");
		if(node->FirstChild() != nullptr)
		{
			value = node->FirstChild()->Value();
			m_RejectInfo.m_sRejectPort=atoi(value.c_str());
			pConfigCenter->SetRejectPort(atoi(value.c_str()));
		}
		
		node = RejectElement->FirstChildElement("RejectMode");
		if(!_stricmp(node->FirstChild()->Value(),"YES"))
		{
			m_RejectInfo.m_bRejectMode = true;
		}
		else
		{
			m_RejectInfo.m_bRejectMode = false;
		}
		node = RejectElement->FirstChildElement("WarningThreshold");
		if(node)
		{
			value = node->FirstChild()->Value();
			pConfigCenter->SetAlarmThreshold(atoi(value.c_str()));
		}

		node = RejectElement->FirstChildElement("EncoderDelaySingleCounts");
		if(node)
		{
			value = node->FirstChild()->Value();
			pConfigCenter->SetEncoderDelaySingleCounts(atoi(value.c_str()));
		}



		node = RejectElement->FirstChildElement("RedLightPort");
		if(node)
		{
			value = node->FirstChild()->Value();
			pConfigCenter->SetRPort(atoi(value.c_str()));
		}

		node = RejectElement->FirstChildElement("GreenLightPort");
		if(node)
		{
			value = node->FirstChild()->Value();
			pConfigCenter->SetGPort(atoi(value.c_str()));
		}

		node = RejectElement->FirstChildElement("TimeInterval");
		if(node)
		{
			value = node->FirstChild()->Value();
			pConfigCenter->SetTimeInterval(atoi(value.c_str()));
		}
	}
}

void ProgramData::LoadBasicSetting(TiXmlElement* pRootElement)
{
	TiXmlElement* BaseInfoElement = pRootElement->FirstChildElement("BasicSetting");
	if (BaseInfoElement != nullptr)
	{
		TiXmlNode* node = BaseInfoElement->FirstChildElement("programname");

		node = BaseInfoElement->FirstChildElement("tlsfilename");
		if(node != nullptr)
		{
			m_sTLSFileName = node->FirstChild()->Value();
		}
		auto ptrConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
		node = BaseInfoElement->FirstChildElement("source");
		if (node != nullptr && !_stricmp(node->FirstChild()->Value(),"FILE"))
			m_eSource = SINGLE_IMG_FILE;
		if (!_stricmp(node->FirstChild()->Value(),"FILES"))
			m_eSource = IMG_FILES;
		if (!_stricmp(node->FirstChild()->Value(),"CAMERA"))
			m_eSource = CAMERA_SOURCE;
		ptrConfigCenter->SetImgSource(m_eSource);

		node = BaseInfoElement->FirstChildElement("imageinterval");
		if(node != nullptr)
		{
			ptrConfigCenter->SetReciveFilesTimeInterval(atoi(node->FirstChild()->Value()));
		}


		Hlong width, height;
		width=0;
		height=0;
		node = BaseInfoElement->FirstChildElement("sourcewindowwidth");
		if (node!=nullptr)
		{
			width = atoi(node->FirstChild()->Value());
		}
		node = BaseInfoElement->FirstChildElement("sourcewindowheight");
		if (node!=nullptr)
		{
			height = atoi(node->FirstChild()->Value());
		}

		ptrConfigCenter->SetDemoImgSize(width, height);

	



		node = BaseInfoElement->FirstChildElement("saveerrimage");
		if (node != nullptr && !_stricmp(node->FirstChild()->Value(),"YES"))
			m_bSaveERRImage = true;
		else
			m_bSaveERRImage = false;
	}
}

void ProgramData::LoadImageSourceSetting(TiXmlElement* pRootElement)
{
	TiXmlElement* ReadFileElement = pRootElement->FirstChildElement("ImageFilePath");
	if (ReadFileElement!=NULL)
	{
		TiXmlNode* node = ReadFileElement->FirstChildElement("FilePath");
		m_sFilePath = node->FirstChild()->Value();
	}
}

void ProgramData::LoadLightIntensitySetting(TiXmlElement* pRootElement)
{
	TiXmlElement* pLightCtrlElement = pRootElement->FirstChildElement("LightIntensitySetting");
	if ((pLightCtrlElement != nullptr))
	{
		SetLightCtrlList(pLightCtrlElement);
	}
}

void ProgramData::SetLightCtrlList(TiXmlElement* pLightCtrlElement)
{
	USES_CONVERSION;
	m_vLightCtrlInfo.clear();

	TiXmlElement *LightLoopElement;	
	TiXmlElement *parameterLoopElement,*propertyElement;
	TiXmlNode *node;
	for (LightLoopElement = pLightCtrlElement->FirstChildElement("lightctrl"); LightLoopElement != nullptr;LightLoopElement = LightLoopElement->NextSiblingElement("lightctrl") )
	{
		LightCtrlInfo data;
		data.m_lightCtrlName = LightLoopElement->FirstAttribute()->Value();
		string strAdd = LightLoopElement->Attribute("address");
		data.m_iaddress      =  _ttoi(A2CT(strAdd.c_str()));

		for (parameterLoopElement = LightLoopElement->FirstChildElement("parameter"); parameterLoopElement;parameterLoopElement = parameterLoopElement->NextSiblingElement("parameter"))
		{
			CHANNEL_PARAMETER channelInfo;
			channelInfo.channelIndex = parameterLoopElement->FirstAttribute()->Value();
			channelInfo.parameterDesc = parameterLoopElement->Attribute("parameterDesc");
			channelInfo.parameterName = parameterLoopElement->Attribute("name");

			channelInfo.settingValue = parameterLoopElement->FirstChildElement("setting")->FirstChild()->Value();
			channelInfo.helpDesc = parameterLoopElement->FirstChildElement("helpdescription")->FirstChild()->Value();
			propertyElement = parameterLoopElement->FirstChildElement("property"); 
			for (node = propertyElement->FirstChildElement();node;node = node->NextSiblingElement())
			{
				string name = node->Value();
				if (name=="listvalue")
				{
					continue;
				}
				string value = node->FirstChild()->Value();
				channelInfo.property_.insert(map<string,string>::value_type(name,value));
				if(!_stricmp(node->FirstChild()->Value(),"ilist"))
				{
					TiXmlNode *ListValueNode;
					TiXmlElement * listvalueyElement = propertyElement->FirstChildElement("listvalue"); 
					channelInfo.valueList.clear();
					for (ListValueNode = listvalueyElement->FirstChildElement();ListValueNode;ListValueNode = ListValueNode->NextSiblingElement())
					{
						string name = ListValueNode->Value();
						channelInfo.valueList.push_back(name);
					}
				}		
			}
			data.m_vParameters.push_back(channelInfo);
		}
		m_vLightCtrlInfo.push_back(data);
	}

	if(CMCtrlCenter::GetSingletonCtrlCenter()->m_VLproxy.TryConnectToUSB(false))
	{
		CMCtrlCenter::GetSingletonCtrlCenter()->m_VLproxy.WriteLightParam2Controller();
	}
}

void ProgramData::SetSampleImageSize()
{
	wstring programPath = CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath();
	string  name = ws2s(programPath);
	name.append(m_sProgramName);
	name.append("\\sample.tiff");
	Hobject image;
	read_image(&image,name.c_str());
	Hlong  lWidth,  lHeight;
	get_image_size(image, &lWidth, &lHeight);
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	pConfigCenter->SetDemoImgSize(lWidth, lHeight);
}

BOOL ProgramData::LoadProgram(wstring openFileName)
{
	string fileName = ws2s(CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath());
	fileName.append(ws2s(openFileName));
	fileName.append("\\process.cfg");
	TiXmlDocument xmlDoc;
	bool loadOkay = xmlDoc.LoadFile(fileName.c_str());
	if (!loadOkay)
	{
		string msg;
		msg = "Could not load test file '";
		msg += fileName;
		msg +="'. Error= ";
		msg += xmlDoc.ErrorDesc();
		msg += ". Exiting.";
		MessageBox(NULL,s2ws(msg).c_str(),theApp.m_strStaionID,MB_OK);
		return FALSE;
	}
	TiXmlElement* pRootElement = xmlDoc.RootElement();
	if ((pRootElement == NULL) || strcmp((pRootElement->Value()),"settings"))
	{
		MessageBox(NULL, _T("Cannot find program_instance"),theApp.m_strStaionID,MB_OK);
		return FALSE;
	}
	m_sProgramName = ws2s(openFileName);
	//SetSampleImageSize();

	LoadBasicSetting(pRootElement);       
	LoadImageSourceSetting(pRootElement); 
	LoadCameraAndLightSetting(pRootElement);
	LoadRejectUnitSetting(pRootElement);
	LoadLightIntensitySetting(pRootElement);

	return true;
}

void ProgramData::SaveCameraAndLightSetting(TiXmlElement* pRootElement)
{
	TiXmlElement * CameraElement = new TiXmlElement( "CameraSetting");
	pRootElement->LinkEndChild( CameraElement ); 

	TiXmlElement * pNode = new TiXmlElement( "CameraName"); 
	pNode->LinkEndChild( new TiXmlText(m_CameraInfo.m_sCameraName.c_str())); 
	CameraElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "TriggerMode"); 
	pNode->LinkEndChild( new TiXmlText((m_CameraInfo.m_bTriggerMode)?"YES":"NO")); 
	CameraElement->LinkEndChild( pNode );

	bool bConnectFlag = CMConfigCenter::GetSingletonConfigCenter()->GetConnect2LightCtrlFlag();
	pNode = new TiXmlElement("Connect2LightCtrlFlag");
	pNode->LinkEndChild(new TiXmlText((bConnectFlag == true?"YES":"NO")));
	CameraElement->LinkEndChild(pNode);

	pNode = new TiXmlElement( "TriggerActivation"); 
	pNode->LinkEndChild( new TiXmlText((m_CameraInfo.m_triggerEdge)?"FallingEdge":"RisingEdge")); 
	CameraElement->LinkEndChild( pNode );

	char tmp[16];
	::memset((void*)tmp, 0x00, 16);
	pNode = new TiXmlElement("CameraGain"); 
	_itoa_s(m_CameraInfo.m_gain,tmp,10);
	pNode->LinkEndChild( new TiXmlText(tmp)); 
	CameraElement->LinkEndChild(pNode);

	::memset((void*)tmp, 0x00, 16);
	pNode = new TiXmlElement("TriggerDelayAbs"); 
	_itoa_s(m_CameraInfo.m_triggerDelayAbs,tmp,10);
	pNode->LinkEndChild( new TiXmlText(tmp)); 
	CameraElement->LinkEndChild(pNode);

	::memset((void*)tmp, 0x00, 16);
	pNode = new TiXmlElement("LinesPerFrame"); 
	_itoa_s(m_CameraInfo.m_linesPerFrame,tmp,10);
	pNode->LinkEndChild( new TiXmlText(tmp)); 
	CameraElement->LinkEndChild(pNode);

	::memset((void*)tmp, 0x00, 16);
	pNode = new TiXmlElement("FramesPerSheet"); 
	_itoa_s(m_CameraInfo.m_framesPerSheet,tmp,10);
	pNode->LinkEndChild( new TiXmlText(tmp)); 
	CameraElement->LinkEndChild(pNode);
}

void ProgramData::SaveRejectUnitSetting(TiXmlElement* pRootElement)
{
	char value[32];
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	TiXmlElement * RejectElement = new TiXmlElement( "RejectSetting"); 
	pRootElement->LinkEndChild( RejectElement ); 

	TiXmlElement* pNode = new TiXmlElement( "port"); 
	_itoa_s(pConfigCenter->GetRejectPort(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "RejectMode"); 
	pNode->LinkEndChild( new TiXmlText(m_RejectInfo.m_bRejectMode?"YES":"NO")); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "WarningThreshold"); 

	memset(value,0,32);
	_itoa_s(pConfigCenter->GetAlarmThreshold(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "RedLightPort"); 
	_itoa_s(pConfigCenter->GetRPort(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "GreenLightPort");
	_itoa_s(pConfigCenter->GetGPort(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "EncoderDelaySingleCounts");
	_itoa_s(pConfigCenter->GetEncoderDelaySingleCounts(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );

	pNode = new TiXmlElement( "TimeInterval");
	_itoa_s(pConfigCenter->GetTimeInterval(),value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	RejectElement->LinkEndChild( pNode );
}

void ProgramData::SaveBasicSetting(TiXmlElement* pRootElement)
{
	TiXmlElement * BaseInfoElement = new TiXmlElement("BasicSetting"); 
	pRootElement->LinkEndChild(BaseInfoElement); 

	TiXmlElement* pNode = new TiXmlElement("programname"); 
	pNode->LinkEndChild( new TiXmlText(m_sProgramName.c_str())); 
	BaseInfoElement->LinkEndChild(pNode);

	pNode = new TiXmlElement("tlsfilename"); 
	pNode->LinkEndChild(new TiXmlText(m_sTLSFileName.c_str())); 
	BaseInfoElement->LinkEndChild( pNode );
	
	char value[32];
	memset((void*)value, 0x00, sizeof(value));
	
	pNode = new TiXmlElement("source"); 	
	if (m_eSource == SINGLE_IMG_FILE)
		pNode->LinkEndChild(new TiXmlText("FILE")); 
	if (m_eSource == IMG_FILES)
		pNode->LinkEndChild(new TiXmlText("FILES")); 
	if (m_eSource == CAMERA_SOURCE)
		pNode->LinkEndChild(new TiXmlText("CAMERA")); 
	if (m_eSource == NONE_SOURCE)
		pNode->LinkEndChild(new TiXmlText("NONE")); 
	BaseInfoElement->LinkEndChild(pNode);

	pNode = new TiXmlElement("imageinterval");
	memset((void*)value, 0x00, sizeof(value));
	_itoa_s(CMConfigCenter::GetSingletonConfigCenter()->GetReciveFilesTimeInterval(), value, 10);
	pNode->LinkEndChild(new TiXmlText(value));
	BaseInfoElement->LinkEndChild(pNode);

	IMAGE_SIZE sz = CMConfigCenter::GetSingletonConfigCenter()->GetDemoImgSize();
	memset((void*)value, 0x00, sizeof(value));
	pNode = new TiXmlElement( "sourcewindowwidth"); 
	_itoa_s(sz.m_ImageWidth,value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	BaseInfoElement->LinkEndChild( pNode );


	pNode = new TiXmlElement( "sourcewindowheight"); 
	memset((void*)value, 0x00, sizeof(value));
	_itoa_s(sz.m_ImageHeight,value,10);
	pNode->LinkEndChild( new TiXmlText(value)); 
	BaseInfoElement->LinkEndChild( pNode );

	pNode = new TiXmlElement("saveerrimage"); 	
	if (m_bSaveERRImage)
	{
		pNode->LinkEndChild(new TiXmlText("YES")); 
	}
	else
		pNode->LinkEndChild(new TiXmlText("NO"));
	BaseInfoElement->LinkEndChild(pNode);
}

void ProgramData::SaveImageSourceSetting(TiXmlElement* pRootElement)
{
	TiXmlElement * ReadFileElement = new TiXmlElement( "ImageFilePath"); 
	pRootElement->LinkEndChild( ReadFileElement ); 

	TiXmlElement* pNode = new TiXmlElement( "FilePath"); 
	pNode->LinkEndChild( new TiXmlText(m_sFilePath.c_str())); 
	ReadFileElement->LinkEndChild( pNode );
}

void ProgramData::SaveLightIntensitySetting(TiXmlElement* pRootElement)
{
	if(m_vLightCtrlInfo.empty())
		return;

	TiXmlElement * lightctrlRoot = new TiXmlElement( "LightIntensitySetting"); 
	pRootElement->LinkEndChild(lightctrlRoot); 
	TiXmlElement* pNode = nullptr;

	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();
	bool bConnected = (pCtrlCenter != nullptr && pCtrlCenter->IsLightCtrollerConnected());
	for (auto it = m_vLightCtrlInfo.begin(); it != m_vLightCtrlInfo.end();it++)
	{
		TiXmlElement* pLightCtrlElement = new TiXmlElement( "lightctrl"); 
		pLightCtrlElement->SetAttribute("name", it->m_lightCtrlName.c_str());
		pLightCtrlElement->SetAttribute("address",(*it).m_iaddress);
		lightctrlRoot->LinkEndChild(pLightCtrlElement); 


		TiXmlElement* lightctrlProperty = new TiXmlElement( "property" ); 
		pLightCtrlElement->LinkEndChild(lightctrlProperty);
		Property *lightctrlPropertyMap = &(it->property_);
		for (auto propertyIt=lightctrlPropertyMap->begin();propertyIt!=lightctrlPropertyMap->end();propertyIt++)
		{
			pNode = new TiXmlElement( propertyIt->first.c_str()); 
			pNode->LinkEndChild( new TiXmlText(propertyIt->second.c_str())); 
			lightctrlProperty->LinkEndChild( pNode );
		}
		auto parameter = it->m_vParameters;

		for (auto parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
		{
			TiXmlElement* parameter = new TiXmlElement( "parameter" ); 
			parameter->SetAttribute("channel", (*parameterIt).channelIndex.c_str());
			parameter->SetAttribute("name", (*parameterIt).parameterName.c_str());
			parameter->SetAttribute("parameterDesc", (*parameterIt).parameterDesc.c_str());

			TiXmlElement* ParamProperty = new TiXmlElement( "property" ); 
			parameter->LinkEndChild(ParamProperty);
			Property *ParamPropertyMap = &((*parameterIt).property_);
			for (auto propertyIt = ParamPropertyMap->begin();propertyIt!=ParamPropertyMap->end();propertyIt++)
			{
				pNode = new TiXmlElement( propertyIt->first.c_str()); 
				pNode->LinkEndChild( new TiXmlText(propertyIt->second.c_str())); 
				ParamProperty->LinkEndChild( pNode );
				if(!_stricmp(propertyIt->second.c_str(),"ilist"))
				{
					TiXmlElement* ParamPropertyListValue = new TiXmlElement( "listvalue" );
					for (auto listValueIt=(*parameterIt).valueList.begin();listValueIt!=(*parameterIt).valueList.end();listValueIt++)
					{
						pNode = new TiXmlElement( (*listValueIt).c_str()); 
						ParamPropertyListValue->LinkEndChild( pNode );
					}
					ParamProperty->LinkEndChild(ParamPropertyListValue);
				}
			}
			pNode = new TiXmlElement( "setting" ); 
			pNode->LinkEndChild( new TiXmlText((*parameterIt).settingValue.c_str())); 
			parameter->LinkEndChild( pNode );

			pNode = new TiXmlElement( "helpdescription" ); 
			pNode->LinkEndChild( new TiXmlText((*parameterIt).helpDesc.c_str())); 
			parameter->LinkEndChild( pNode );
			pLightCtrlElement->LinkEndChild(parameter);
		}
	}
	// Write light controller parameter into Frameware
	if(bConnected)
	{
		try
		{
			std::for_each(m_vLightCtrlInfo.begin(), m_vLightCtrlInfo.end(), [&](LightCtrlInfo& info)
			{
				pCtrlCenter->m_VLproxy.SelectAdd((byte)info.m_iaddress);
				pCtrlCenter->m_VLproxy.EEPROM();
			});
		}
		catch(...)
		{
			// AfxMessageBox here
		}
	}
}

void ProgramData::SaveProgramData()
{
	string TestProgramPath;
	TestProgramPath = ws2s(CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath());
	TestProgramPath += m_sProgramName;

	string cfgfileName= TestProgramPath + "\\process.cfg";
	TiXmlDocument xmlDoc(cfgfileName.c_str());
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0","gb2312", "yes" ); // 声明XML的属性
	xmlDoc.LinkEndChild( decl ); 

	TiXmlElement* pRootElement = new TiXmlElement( "settings" );
	xmlDoc.LinkEndChild(pRootElement) ;

	SaveCameraAndLightSetting(pRootElement);
	SaveRejectUnitSetting(pRootElement);
	SaveBasicSetting(pRootElement);
	SaveImageSourceSetting(pRootElement);
	SaveLightIntensitySetting(pRootElement);

	xmlDoc.Print() ;
	xmlDoc.SaveFile(); // 把XML文件写入硬盘		
}

