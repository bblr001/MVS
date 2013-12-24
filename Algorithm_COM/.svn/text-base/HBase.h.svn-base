/*****************************************************************************
 * HBase.h
 ***************************************************************************** 
 *
 * Project:     HALCON/libhalcon
 * Description: Basic definitions for HALCON, HALCON/C, HALCON/C++
 *              and other language interfaces
 *
 * (c) 1996-2010 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 * $Revision: 1.37 $
 * $Date: 2010/08/27 08:23:30 $
 *
 */



#ifndef HBASE_H
#define HBASE_H

#include <stdlib.h> /* NULL */

typedef   void*   VOIDP;

/*****************************************************************************/
/* Parameter passing (Control parameters)                                    */
/*****************************************************************************/
#define LONG_PAR         1       /* Parameter type: long                     */
#define FLOAT_PAR        2       /* Parameter type: float                    */
#define STRING_PAR       4       /* Parameter type: string                   */
#define INT_PAR      LONG_PAR    /* Parameter type: int                      */
#define DOUBLE_PAR  FLOAT_PAR    /* Parameter type: double                   */
#define UNDEF_PAR       32       /* Parameter type: no defined type          */
#define POINTER_PAR     64       /* Parameter type: pointer to any type      */
#define TUPLE_PAR      128       /* Parameter type: pointer to tuple         */
#define ANY_PAR          7       /* Parameter type: arbitrary                */


/*****************************************************************************/
/* Return values of HALCON operators in the case of no error (messages)      */
/*****************************************************************************/
#define H_MSG_OK          1          /* Normal return value                  */
#define H_MSG_TRUE        2          /* TRUE                                 */
#define H_MSG_FALSE       3          /* FALSE                                */
#define H_MSG_VOID        4          /* Stop processing                      */
#define H_MSG_FAIL        5          /* Call failed                          */


/*****************************************************************************/
/* Constants and basic types                                                 */
/*****************************************************************************/
#define MAX_TUPLE_LENGTH 1000000   /* max. length of a tuple                 */
#define MAX_STRING       1024      /* max. length of a string                */

typedef UINT4            Herror;   /* Type function values (error messages)  */

typedef  long *Hkey;               /* primary key in DB (for iconic objects) */
#define  UNDEF_KEY   (Hkey)(0)     /* Undefined iconic object                */
		 

/*****************************************************************************/
/* Structures for passing parameters between language interface and core     */
/*****************************************************************************/
typedef union 
{
  INT4_8  l;              /* 4/8 byte integer                       (input)  */
  double  f;              /* 8 byte real                            (input)  */
  char    *s;             /* pointer to strings                     (input)  */
} Hpar;                   /* parameter passing for the C interface           */

typedef union 
{
  INT4_8  *l;             /* 4/8 byte integer                       (output) */
  double  *f;             /* 8 byte real                            (output) */
  char    *s;             /* pointer to strings                     (output) */
  VOIDP   p;              /* pointer to var. of any type (e.g. tuple)(output)*/
} Hvar;                   /* parameter passing for the C interface           */

typedef struct
{
  Hpar   par;             /* values                                          */
  INT1   type;            /* type flag                                       */
} Hcpar;                  /* parameter passing for the C interface           */

typedef struct
{
  Hvar   var;             /* values                                          */
  UINT1  type;            /* type flag                                       */
} Hcvar;                  /* parameter passing for the C interface           */

typedef struct
{
  Hcpar   *element;       /* tuple element(s)                                */
  INT4_8  num_el;         /* number of used elements                         */
  INT4_8  length;         /* total length of array (incl. unused elements)   */
} Hctuple;                /* for managing output control parameters          */

typedef struct
{
  Hcvar   *variables;     /* variables (of application) to write back values */
  Hcpar   *element;       /* tuple element(s)                                */
  INT4_8  num_el;         /* number of used elements                         */
  INT4_8  length;         /* total length of array (incl. unused elements)   */
} Hcvtuple;               /* for passing control parameter variables from    */
                          /* the language to the core interface              */


/*****************************************************************************/
/* Bool constants                                                            */
/*****************************************************************************/
#ifndef TRUE
#define TRUE             1
#else
#undef  TRUE
#define TRUE             1
#endif

#ifndef FALSE
#define FALSE            0
#else
#undef  FALSE
#define FALSE            0
#endif


/*****************************************************************************/
/* Pixel types of HALCON images                                              */
/*****************************************************************************/
#define UNDEF_IMAGE   (INT)0 
#define BYTE_IMAGE    (INT)(1<<0)
#define INT4_IMAGE    (INT)(1<<1)  
#define LONG_IMAGE    INT4_IMAGE
#define FLOAT_IMAGE   (INT)(1<<2)
#define DIR_IMAGE     (INT)(1<<3)
#define CYCLIC_IMAGE  (INT)(1<<4)
#define INT1_IMAGE    (INT)(1<<5)
/* (1<<6) omitted sofar -> use it for next new image type */
#define COMPLEX_IMAGE (INT)(1<<7)
/* (1<<8) omitted sofar -> use it for next new image type */
#define INT2_IMAGE    (INT)(1<<9)
#define UINT2_IMAGE   (INT)(1<<10)
#define VF_IMAGE      (INT)(1<<11)
#define INT8_IMAGE    (INT)(1<<12)


/*****************************************************************************/
/* HALCON procedure (operator) handle                                        */
/*****************************************************************************/
/* This data structure contains all informations about an instance of an     */
/* HALCON operator or an HALCON thread derived from an HALCON operator       */
/* instance. The contained information describes the processing context of   */
/* HALCON operators (e.g. parameter values, debugging information, etc.).    */
/*****************************************************************************/
typedef void *Hproc_handle;


/*****************************************************************************/
/* data types for handling pthreads (POSIX threads) and mutex variables      */
/*****************************************************************************/
typedef void*          H_pthread_t;            /* pthread handle             */
typedef void*          H_pthread_mutex_t;      /* pthread mutex data type    */
typedef void*          H_pthread_cond_t;       /* pthread condition variable */
typedef void*          H_pthread_barrier_t;    /* pthread barrier variable */


/* a define for the restrict qualifier */
#if !defined(restrict)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* compiler is in C99 mode and should know about the restrict qualifier */
# else
#  if (defined(_WIN32) && defined(_MSC_VER) && _MSC_VER >= 1400) || defined(__INTEL_COMPILER)
/* Intel Compilers and grown-up Microsoft Compilers always know a __restrict */
#   define restrict __restrict
#  else
#   if defined(__linux) && defined(__GNUC__)
#    define restrict __restrict__
#   else
#    define restrict
#   endif
#  endif
# endif /* __STDC_VERSION__ */
#endif /* restrict */

/*
 * gcc 3.4.3 (used for the Eneo port) has problems using the 'restrict'
 * keyword on arrays of (restricted) pointers.
 * Therefore, always use RESTRICT in that kind: *RESTRICT *
 */
#if defined restrict && defined(__GNUC__) && (__GNUC__ <= 3)
#  define RESTRICT
#else
#  define RESTRICT restrict
#endif
 

/* a define for the inline qualifier */
#if !defined(H_INLINE)
#ifdef __cplusplus
#define H_INLINE inline
#else
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
/* compiler is in C99 mode and should know about the inline qualifier */
#  define H_INLINE inline
#else
#if defined(_WIN32) || defined(__alpha) || defined(__sgi)
#  define H_INLINE __inline
#else
#if defined(__linux)
#  define H_INLINE __inline__
#else
#if defined(__sun)
#  define H_INLINE inline
#else
#  define H_INLINE
#endif
#endif
#endif
#endif /* __STDC_VERSION__ */
#endif /* #ifdef __cplusplus .. else */
#endif /* H_INLINE */

#endif
