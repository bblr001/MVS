/*****************************************************************************
 * HVersNum.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Current version of the HALCON library
 *
 * (c) 1996-2011 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.71.2.8 $
 * $Date: 2011/04/14 15:18:06 $
 *
 */


#ifndef HLIB_VERSION
#define HLIB_VERSION          "10.0"
#endif

#ifndef HLIB_VERSION_NUM
#define HLIB_VERSION_NUM      10.0
#endif

#ifndef HLIB_LAST_UPDATE
#define HLIB_LAST_UPDATE      "14.04.2011"
#endif

#ifndef HLIB_REVISION
#define HLIB_REVISION         "1"
#endif

#ifndef HALCON_VERSION_CODE
#define HALCON_VERSION_CODE 0x0A0001
#endif

#ifndef HALCON_VERSION
#define HALCON_VERSION(major,minor,revision) \
  (((major)<<16) + ((minor)<<8) + (revision))
#endif
