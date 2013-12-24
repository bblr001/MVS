/*****************************************************************************
 * HExtern.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: External variables and some global procedures for 
 *              language interfaces
 *
 * (c) 1996-2010 by MVTec Software GmbH
 *                  www.mvtec.com
 * 
 *****************************************************************************
 *
 * $Revision: 1.3.2.1 $
 * $Date: 2010/10/20 14:26:50 $
 *
 */

#ifndef HEXTERN_H
#define HEXTERN_H

#if defined(__cplusplus)
extern "C" {
#endif

/* global variables for image processing                                     */
extern HLibExport H_SYS_INFO_READ_ONLY HROInfo; /* global read-only data     */
extern HLibExport H_OPERATOR_INFO HProcInfo[MAX_PROC]; 
                                                /* procedures description    */
extern HLibExport INT          HDoLowError;     /* error messages of HALCON  */
extern HLibExport INT4         HLowErrorAction[4]; /* action for HALCON low  */
                                                   /* level error messages   */
extern HLibExport INT          HDoLicenseError; /* license msgs of HALCON    */
extern HLibExport INT          HUseSpinLock;    /* sync initialization of 
                                                 * Parallel HALCON           */
extern HLibExport INT          HStartUpThreadPool;  /* start thread pool 
                                                     * initially? */
extern HLibExport INT          HShutdownThreadPool; /* shutdown thread pool 
                                                     * on termination? */


/* Convenience function accessors as some development environments */
/* do not directly support importing variables from C DLLs.        */

extern HLibExport void __stdcall HSetDoLicenseError(INT value);
extern HLibExport void __stdcall HSetUseSpinLock(INT value);
extern HLibExport void __stdcall HSetStartUpThreadPool(INT value);
extern HLibExport void __stdcall HSetShutdownThreadPool(INT value);

extern HLibExport INT __stdcall HGetDoLicenseError();
extern HLibExport INT __stdcall HGetUseSpinLock();
extern HLibExport INT __stdcall HGetStartUpThreadPool();
extern HLibExport INT __stdcall HGetShutdownThreadPool();

extern HLibExport H_SYS_INFO_EXCLUSIVE *my_sys_info_excl;
extern HLibExport H_SYS_INFO_SHARED my_sys_info_shared;  /* gl. HALCON var.s */
/* remark: the structure above contains global HALCON system variables       */
/* which are (in the normal case) exclusively accessible via a valid         */
/* procedure handle and by using specific functions of the HALCON-Lib        */
/* source code file HInstance.c; those functions contain synchronization     */
/* mechanisms to guarantee a correct access to the variables even in case of */
/* a parallel/multithreaded/reentrant HALCON version.                        */
/* Nevertheless the structure is propagated here so that it also can be used */
/* directly, but this should be done VERY CAREFULLY!! At the moment it is    */
/* only used directly within HDevelop, which means no problem, because       */
/* HDevelop works strictly sequentially, i.e. it calls all HALCON            */
/* operators one after another;                                              */

#if defined(__cplusplus)
}
#endif

#endif
