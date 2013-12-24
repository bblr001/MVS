#ifndef __ACTION_HALCON_HEADER__
#define __ACTION_HALCON_HEADER__
#include "CMData.h"
#include <map>
#include <string>
namespace AAction
{
	using namespace Halcon;
	namespace Acquirsition{
	  extern void InitializeRead();
	  extern void SetPath(string path);
	  extern void InitAssign(Hobject&);
	  extern inline void acquire(CMData *pData);
	};
	namespace INSPECTIONMeasure
	{
		extern list<STDoProcess>* m_pDoProcessList;
		extern void display_init();
		extern void display_close();
		extern inline void action(CMData * pData);
		extern inline void display(CMData * pData);
	};
};
namespace MandrillRegionOp=AAction::INSPECTIONMeasure;
#endif