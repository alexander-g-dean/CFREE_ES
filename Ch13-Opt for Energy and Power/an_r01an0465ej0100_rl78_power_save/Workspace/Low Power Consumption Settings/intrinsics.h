/*-------------------------------------------------------------------------
 *      Declarations of intrinsic functions.
 *
 *      This header file can be used with the
 *      IAR RL78 C/C++ compilers, ICCRL78.
 *
 *      Copyright 2011 IAR Systems AB.
 *
 *      $Revision: 205 $
 *
 *-----------------------------------------------------------------------*/

#ifndef __INTRINSICS_INCLUDED
#define __INTRINSICS_INCLUDED

#ifndef __ICCRL78__
  #error "INTRINSICS.H file for use with ICCRL78 only"
#endif

#pragma language=extended
#pragma system_include

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char __istate_t;

__intrinsic void __disable_interrupt(void);
__intrinsic void __enable_interrupt(void);
__intrinsic __istate_t __get_interrupt_state(void);
__intrinsic void __set_interrupt_state(__istate_t);

__intrinsic void __no_operation(void);
__intrinsic void __halt(void);
__intrinsic void __stop(void);
__intrinsic void __break(void);

__intrinsic __root int __low_level_init(void);

#if __CORE__ == __RL78_2__
__intrinsic void __mach(signed short, signed short);
__intrinsic void __machu(unsigned short, unsigned short);

#endif
#pragma language=default

#ifdef __cplusplus
}
#endif

#endif  /* __INTRINSICS_INCLUDED */
