/*UNCRUSTIFY-OFF*/
/**
 * @file defines.h
 * @author Manny Peterson <manny@heliosproj.org>
 * @brief Kernel source for macro definitions
 * @version 0.5.0
 * @date 2023-03-19
 * 
 * @copyright
 * HeliOS Embedded Operating System Copyright (C) 2020-2023 HeliOS Project <license@heliosproj.org>
 *  
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  
 * 
 */
/*UNCRUSTIFY-ON*/
#ifndef DEFINES_H_
  #define DEFINES_H_

  #include "posix.h"

  #include <limits.h>
  #include <stdint.h>
  #include <stddef.h>


  #if defined(CHAR_BIT)
    #if CHAR_BIT != 8
      #pragma message("WARNING: System may not have an 8-bit wide byte!")
    #endif /* if CHAR_BIT != 8 */
  #else  /* if !defined(CHAR_BIT) */
    #pragma message("WARNING: Unable to determine if system has an 8-bit wide byte. CHAR_BIT not defined?")
  #endif /* if !defined(CHAR_BIT) */


  #if defined(true)
    #undef true
  #endif /* if defined(true) */
  #define true 0xFFu /* 255*/


  #if defined(false)
    #undef false
  #endif /* if defined(false) */
  #define false 0x0u /* 0 */


  #if defined(null)
    #undef null
  #endif /* if defined(null) */
  #if defined(__cplusplus)
    #define null 0x0 /* 0 */
  #else  /* if defined(__cplusplus) */
    #define null ((void *) 0x0) /* 0 */
  #endif /* if defined(__cplusplus) */


  #if defined(nil)
    #undef nil
  #endif /* if defined(nil) */
  #define nil 0x0u /* 0 */


  #if defined(OS_PRODUCT_NAME_SIZE)
    #undef OS_PRODUCT_NAME_SIZE
  #endif /* if defined(OS_PRODUCT_NAME_SIZE) */
  #define OS_PRODUCT_NAME_SIZE 0x6u /* 6 */


  #if defined(MEMORY_REGION_SIZE_IN_BYTES)
    #undef MEMORY_REGION_SIZE_IN_BYTES
  #endif /* if defined(MEMORY_REGION_SIZE_IN_BYTES) */
  #define MEMORY_REGION_SIZE_IN_BYTES CONFIG_MEMORY_REGION_SIZE_IN_BLOCKS *CONFIG_MEMORY_REGION_BLOCK_SIZE


  #if defined(RUNNING)
    #undef RUNNING
  #endif /* if defined(RUNNING) */
  #define RUNNING flag.running


  #if defined(OVERFLOW)
    #undef OVERFLOW
  #endif /* if defined(OVERFLOW) */
  #define OVERFLOW flag.overflow


  #if defined(MEMFAULT)
    #undef MEMFAULT
  #endif /* if defined(MEMFAULT) */
  #define MEMFAULT flag.memfault


  #if defined(LITTLEEND)
    #undef LITTLEEND
  #endif /* if defined(LITTLEEND) */
  #define LITTLEEND flag.littleend


  #if defined(SETFLAG)
    #undef SETFLAG
  #endif /* if defined(SETFLAG) */
  #define SETFLAG(flag_) (flag_ = 0xFFu)


  #if defined(UNSETFLAG)
    #undef UNSETFLAG
  #endif /* if defined(UNSETFLAG) */
  #define UNSETFLAG(flag_) (flag_ = 0x0u)


  #if defined(FLAGSET)
    #undef FLAGSET
  #endif /* if defined(FLAGSET) */
  #define FLAGSET(flag_) (0xFFu == (flag_))


  #if defined(FLAGNOTSET)
    #undef FLAGNOTSET
  #endif /* if defined(FLAGNOTSET) */
  #define FLAGNOTSET(flag_) (0x0u == (flag_))


  #if defined(NOTNULLPTR)
    #undef NOTNULLPTR
  #endif /* if defined(NOTNULLPTR) */
  #define NOTNULLPTR(addr_) (null != (addr_))


  #if defined(NULLPTR)
    #undef NULLPTR
  #endif /* if defined(NULLPTR) */
  #define NULLPTR(addr_) (null == (addr_))


  #if defined(RET_DEFINE)
    #undef RET_DEFINE
  #endif /* if defined(RET_DEFINE) */
  #define RET_DEFINE Return_t ret = ReturnError


  #if defined(RET_RETURN)
    #undef RET_RETURN
  #endif /* if defined(RET_RETURN) */
  #define RET_RETURN return(ret)


  #if defined(RET_OK)
    #undef RET_OK
  #endif /* if defined(RET_OK) */
  #define RET_OK ret = ReturnOK


  #if defined(OK)
    #undef OK
  #endif /* if defined(OK) */
  #define OK(expr_) (ReturnOK == (expr_))


  #if defined(ERROR)
    #undef ERROR
  #endif /* if defined(ERROR) */
  #define ERROR(expr_) (ReturnError == (expr_))


  #if defined(ASSERT)
    #undef ASSERT
  #endif /* if defined(ASSERT) */
  #if defined(CONFIG_ENABLE_SYSTEM_ASSERT)
    #define ASSERT xSystemAssert(__FILE__, __LINE__)
  #else  /* if defined(CONFIG_ENABLE_SYSTEM_ASSERT) */
    #define ASSERT
  #endif /* if defined(CONFIG_ENABLE_SYSTEM_ASSERT) */


  #if defined(MEMORY_REGION_CHECK_OPTION_WO_ADDR)
    #undef MEMORY_REGION_CHECK_OPTION_WO_ADDR
  #endif /* if defined(MEMORY_REGION_CHECK_OPTION_WO_ADDR) */
  #define MEMORY_REGION_CHECK_OPTION_WO_ADDR 0x1u /* 1 */


  #if defined(MEMORY_REGION_CHECK_OPTION_W_ADDR)
    #undef MEMORY_REGION_CHECK_OPTION_W_ADDR
  #endif /* if defined(MEMORY_REGION_CHECK_OPTION_W_ADDR) */
  #define MEMORY_REGION_CHECK_OPTION_W_ADDR 0x2u /* 2 */


  #if defined(UINT8_TYPE)
    #undef UINT8_TYPE
  #endif /* if defined(UINT8_TYPE) */
  #define UINT8_TYPE uint8_t


  #if defined(UINT16_TYPE)
    #undef UINT16_TYPE
  #endif /* if defined(UINT16_TYPE) */
  #define UINT16_TYPE uint16_t


  #if defined(UINT32_TYPE)
    #undef UINT32_TYPE
  #endif /* if defined(UINT32_TYPE) */
  #define UINT32_TYPE uint32_t


  #if defined(SIZE_TYPE)
    #undef SIZE_TYPE
  #endif /* if defined(SIZE_TYPE) */
  #define SIZE_TYPE size_t


  #if defined(VOID_TYPE)
    #undef VOID_TYPE
  #endif /* if defined(VOID_TYPE) */
  #define VOID_TYPE void


#endif /* ifndef DEFINES_H_ */