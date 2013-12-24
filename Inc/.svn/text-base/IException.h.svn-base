#pragma once

#include "CBaseException.h"
namespace Exception
{
  class IException : public CBaseException  
  {
  public:
	  IException( Exception::ErrorNumber e, string context = ( "" ), va_list *pArgs = NULL );
	  IException(  Exception::ErrorNumber e, string context , PVOID pArg  );
  private:
	  static const string m_LibraryFile;
   
  };
}
