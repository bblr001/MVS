// Exception.h: interface for the Exception class.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include <assert.h>
#include <string>
using namespace std;

namespace Exception
{

/// The Error Numbers
	typedef unsigned long ErrorNumber;

	class CBaseException  
	{
	public:
	  CBaseException( ErrorNumber e, string context = "", va_list *pArgs = NULL );
	  CBaseException( ErrorNumber e, string context , PVOID pArg  );
	  CBaseException( ErrorNumber e, string context, bool initonly );
	  virtual ~CBaseException();

	  /// retrieve the error code
	  ErrorNumber Error() const
	  {
		return m_Error;
	  }
	  /// retrieve the error message
	  string Description() const
	  {
		return m_Description;
	  }
	  /// retrieve additional context information
	  string Context() const
	  {
		return m_Context;
	  }
	protected:
	  /// creates a new message
	  void FormatMessage( char** ppArgs );
	  //virtual void FormatMessage( const CString& LibraryFile, char** ppArgs );
	protected:

	  ErrorNumber m_Error;
	  string m_Description;
	  string m_Context;
	};

	inline CBaseException::CBaseException( ErrorNumber e, string context, va_list *pArgs )
	: m_Error( e ), m_Context( context )
	{
	  FormatMessage( (char**) pArgs );
	}

	inline CBaseException::CBaseException( ErrorNumber e, string context , PVOID pArg  )
	: m_Error( e ), m_Context( context )
	{
	  FormatMessage( (char**) pArg );
	}

	inline CBaseException::CBaseException( ErrorNumber e,string context, bool /*initonly*/ )
	: m_Error( e ), m_Context( context )
	{
	}

	inline void CBaseException::FormatMessage( char** ppArgs )
	{
	  const string NoResourceFile;
	  //FormatMessage( NoResourceFile, ppArgs );
	}

	//inline void CBaseException::FormatMessage( const string& LibraryFile, char** ppArgs )
	//{
	  // Try to get an error message by using FormatMessage
	  // Search sequence: 1. m_LibraryFile
	  //                  2. System
	  //                  3. Application program
	  
	//}

	inline CBaseException::~CBaseException()
	{

	}

}
