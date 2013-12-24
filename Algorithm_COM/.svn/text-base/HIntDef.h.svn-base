/*****************************************************************************
 * HIntDef.h
 *****************************************************************************
 *
 * Project:     HALCON/libhalcon
 * Description: Definition of integer data types
 *              These definitions can be controlled by the compiler
 *
 * (c) 1996-2010 by MVTec Software GmbH
 *                  www.mvtec.com
 *
 *****************************************************************************
 *
 *  $Revision: 1.25 $
 *  $Date: 2010/05/03 13:49:24 $
 *
 */

#ifndef HINTDEF_H
#define HINTDEF_H

#ifndef __midl
#  include <stdlib.h> /* RAND_MAX */
#  include <float.h>  /* FLT_MAX, DBL_MAX, ... */
#  include <limits.h> /* LONG_MAX, INT_MAX, ... */
#endif

#ifdef _WIN32
# ifndef __midl
#  include <windows.h>
# endif
#else
#  define  INT      int               /* integer, signed   2-8 Byte      */
#  define  UINT     unsigned int      /* integer, unsigned 2-8 Byte      */
#  define  UINT_MIN 0
#endif

#ifndef _INT16
#  define _INT16      short
#  define _INT16_MIN  SHRT_MIN
#  define _INT16_MAX  SHRT_MAX
#  define _UINT16_MIN 0
#  define _UINT16_MAX USHRT_MAX
#endif

#ifndef _INT32
#  define _INT32      int
#  define _INT32_MIN  INT_MIN
#  define _INT32_MAX  INT_MAX
#  define _UINT32_MIN 0
#  define _UINT32_MAX UINT_MAX
#endif


/* _INT64 is 64-bit only on 64-bit platforms */
#ifndef _WIN64 /* LP64 data model */
#  if !defined(_TMS320C6X)
#    define _INT64        long
#    define _INT64_FORMAT "l"
#    define _INT64_MIN    LONG_MIN
#    define _INT64_MAX    LONG_MAX
#    define _UINT64_MIN   0UL
#    define _UINT64_MAX   ULONG_MAX
#  else       /* _TMS320C6X long is really 40Bit, but sizeof(long)=8 */
#    define _INT64        int
#    define _INT64_FORMAT ""
#    define _INT64_MIN    INT_MIN
#    define _INT64_MAX    INT_MAX
#    define _UINT64_MIN   0
#    define _UINT64_MAX   UINT_MAX
#  endif
#else         /* LLP64 data model */
#  define _INT64        __int64
#  define _INT64_FORMAT "I64"
#  define _INT64_MIN    _I64_MIN
#  define _INT64_MAX    _I64_MAX
#  define _UINT64_MIN   0UL
#  define _UINT64_MAX   _UI64_MAX
#endif

/* _INT64F is forced to 64-bit even on 32-bit platforms if supported */
#if defined(_WIN32) || defined(_WIN64)
#  define _INT64F        __int64
#  define _INT64F_FORMAT "I64"
#  define _INT64F_MIN    _I64_MIN
#  define _INT64F_MAX    _I64_MAX
#  define _UINT64F_MIN   0UL
#  define _UINT64F_MAX   _UI64_MAX
#else
#  if defined(__alpha)
#    define _INT64F        long
#    define _INT64F_FORMAT "l"
#    define _INT64F_MIN    LONG_MIN
#    define _INT64F_MAX    LONG_MAX
#    define _UINT64F_MIN   0UL
#    define _UINT64F_MAX   ULONG_MAX
#  else
#    define _INT64F        long long
#    define _INT64F_FORMAT "ll"
#    ifndef LLONG_MAX
#      define LLONG_MAX    9223372036854775807LL
#    endif
#    ifndef LLONG_MIN
#      define LLONG_MIN    (-LLONG_MAX-1LL)
#    endif
#    ifndef ULLONG_MAX
#      define ULLONG_MAX   18446744073709551615ULL
#    endif
#    define _INT64F_MIN    LLONG_MIN
#    define _INT64F_MAX    LLONG_MAX
#    define _UINT64F_MIN   0ULL
#    define _UINT64F_MAX   ULLONG_MAX
#    endif
#endif


/* At least an address must fit into MACHINE_WORD */
#define _MACHINE_WORD _INT64

#define  MACHINE_WORD _MACHINE_WORD /* only for memory management     */
                                    /* (HAlloc.c)                     */

#ifndef _DOUBLE8
#  define DOUBLE8   double
#else
#  ifndef TRIMEDIA
#    define DOUBLE8 _DOUBLE8
#  else
#    define DOUBLE8 long double
#  endif
#endif

#ifdef SPARC
#  ifndef DBL_MAX
#    define DBL_MAX MAXDOUBLE
#  endif
#  ifndef DBL_MIN
#    define DBL_MIN MINDOUBLE
#  endif
#  ifndef FLT_MAX
#    define FLT_MAX MAXFLOAT
#  endif
#  ifndef FLT_MIN
#    define FLT_MIN MINFLOAT
#  endif
#endif

#ifdef __vxworks
#  include <types/vxTypesBase.h>
#  ifndef DBL_MAX
#    define DBL_MAX _ARCH_DBL_MAX
#  endif
#  ifndef DBL_MIN
#    define DBL_MIN _ARCH_DBL_MIN
#  endif
#  ifndef FLT_MAX
#    define FLT_MAX _ARCH_FLT_MAX
#  endif
#  ifndef FLT_MIN
#    define FLT_MIN _ARCH_FLT_MIN
#  endif
#endif

#ifndef FLT_EPSILON
#  define FLT_EPSILON 1E-5
#endif

#ifndef RAND_MAX
#  define RAND_MAX MAXINT
#endif


#if defined(__CHAR_UNSIGNED__) || defined(__sgi) 
#define  INT1      signed char       /* integer, signed 1 Byte         */
#define  INT1_MIN  SCHAR_MIN
#define  INT1_MAX  SCHAR_MAX
#else
#define  INT1      char              /* integer, signed 1 Byte         */
#define  INT1_MIN  CHAR_MIN
#define  INT1_MAX  CHAR_MAX
#endif
#define  UINT1     unsigned char     /* integer, unsigned 1 Byte       */
#define  UINT1_MIN 0
#define  UINT1_MAX UCHAR_MAX


#define  INT2      _INT16            /* integer, signed 2 Byte         */
#define  INT2_MIN  _INT16_MIN
#define  INT2_MAX  _INT16_MAX
#define  UINT2     unsigned _INT16   /* integer, unsigned 2 Byte       */
#define  UINT2_MIN _UINT16_MIN
#define  UINT2_MAX _UINT16_MAX


#define  INT4      _INT32            /* integer, signed 4 Byte         */
#define  INT4_MIN  _INT32_MIN
#define  INT4_MAX  _INT32_MAX
#define  UINT4     unsigned _INT32   /* integer, unsigned 4 Byte       */
#define  UINT4_MIN _UINT32_MIN
#define  UINT4_MAX _UINT32_MAX


#define  INT4_8      _INT64          /* integer, signed 4-8 Byte       */
#define  INT4_8_MIN  _INT64_MIN
#define  INT4_8_MAX  _INT64_MAX
#define  UINT4_8     unsigned _INT64 /* integer, unsigned 4-8 Byte     */
#define  UINT4_8_MIN _UINT64_MIN
#define  UINT4_8_MAX _UINT64_MAX

#define LONG_FORMAT _INT64_FORMAT
typedef INT4_8  Hlong;
typedef UINT4_8 Hulong;

#define  HINT8      _INT64F          /* integer, signed 8 Byte         */
#define  HINT8_MIN  _INT64F_MIN
#define  HINT8_MAX  _INT64F_MAX
#define  HUINT8     unsigned _INT64F /* integer, unsigned 8 Byte       */
#define  HUINT8_MIN _UINT64F_MIN
#define  HUINT8_MAX _UINT64F_MAX

#define LLONG_FORMAT _INT64F_FORMAT


#if !defined(HC_LARGE_IMAGES)
#define HIMGCOOR_MIN INT2_MIN
#define HIMGCOOR_MAX INT2_MAX
#define HITEMCNT_MIN INT4_MIN
#define HITEMCNT_MAX INT4_MAX
#define HSUBCOOR_MIN FLT_MIN
#define HSUBCOOR_MAX FLT_MAX
#define HSUBATTR_MIN FLT_MIN
#define HSUBATTR_MAX FLT_MAX
#else
#define HIMGCOOR_MIN INT4_MIN
#define HIMGCOOR_MAX INT4_MAX
#define HITEMCNT_MIN INT4_8_MIN
#define HITEMCNT_MAX INT4_8_MAX
#define HSUBCOOR_MIN DBL_MIN
#define HSUBCOOR_MAX DBL_MAX
#define HSUBATTR_MIN DBL_MIN
#define HSUBATTR_MAX DBL_MAX
#endif


#endif
