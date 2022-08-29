/**
 * @file port.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel sources for portability layer
 * @version 0.3.5
 * @date 2022-03-24
 *
 * @copyright
 * HeliOS Embedded Operating System
 * Copyright (C) 2020-2022 Manny Peterson <mannymsp@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "port.h"


#if defined(ARDUINO_ARCH_AVR)

Ticks_t __SysGetSysTicks__(void) {

  return timer0_overflow_count;
}

void __SysInit__(void) {

  return;
}

#elif defined(ARDUINO_ARCH_SAM)

Ticks_t __SysGetSysTicks__(void) {

  return GetTickCount();
}

void __SysInit__(void) {

  return;
}

#elif defined(ARDUINO_ARCH_SAMD)

Ticks_t __SysGetSysTicks__(void) {

  return millis();
}

void __SysInit__(void) {

  return;
}

#elif defined(ARDUINO_ARCH_ESP8266)

Ticks_t __SysGetSysTicks__(void) {
  
  yield();

  return (Ticks_t)(system_get_time() / 1000ULL);
}

void __SysInit__(void) {

  return;
}

#elif defined(ARDUINO_TEENSY_MICROMOD) || defined(ARDUINO_TEENSY40) || defined(ARDUINO_TEENSY41) || defined(ARDUINO_TEENSY36) || defined(ARDUINO_TEENSY35) || defined(ARDUINO_TEENSY31) || defined(ARDUINO_TEENSY32) || defined(ARDUINO_TEENSY30) || defined(ARDUINO_TEENSYLC)

Ticks_t __SysGetSysTicks__(void) {

  return systick_millis_count;
}

void __SysInit__(void) {

  return;
}

#elif defined(ESP32)

/* Not supported. */

#elif defined(CMSIS_ARCH_CORTEXM)

static volatile Ticks_t sysTicks = zero;

void SysTick_Handler(void) {

  DISABLE_INTERRUPTS();

  sysTicks++;

  ENABLE_INTERRUPTS();

  return;
}

Ticks_t __SysGetSysTicks__(void) {

  return sysTicks;
}

void __SysInit__(void) {

  SysTick_Config(SYSTEM_CORE_CLOCK_FREQUENCY / SYSTEM_CORE_CLOCK_PRESCALER);

  return;
}

#elif defined(POSIX_ARCH_OTHER)

Ticks_t __SysGetSysTicks__(void) {

  struct timeval t;

  gettimeofday(&t, NULL);


  return (t.tv_sec) * 1000 + (t.tv_usec) / 1000;
}

void __SysInit__(void) {

  return;
}

#endif
