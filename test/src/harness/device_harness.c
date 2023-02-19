/*UNCRUSTIFY-OFF*/
/**
 * @file device_harness.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief
 * @version 0.4.0
 * @date 2022-09-02
 *
 * @copyright
 * HeliOS Embedded Operating System
 * Copyright (C) 2020-2023 Manny Peterson <mannymsp@gmail.com>
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
/*UNCRUSTIFY-ON*/
#include "device_harness.h"


void device_harness(void) {
  Size_t bytes1;
  Addr_t *data1;
  Size_t bytes2;
  Addr_t *data2;
  Word_t *data3;
  Word_t *data4;
  Base_t res;


  unit_begin("xDeviceRegisterDevice()");
  unit_try(OK(xDeviceRegisterDevice(LOOPBACK_self_register)));
  unit_end();
  unit_begin("xDeviceWrite()");
  bytes1 = 0x26u;
  data1 = null;
  unit_try(OK(xMemAlloc((volatile Addr_t **) &data1, bytes1)));
  memcpy(data1, "THIS IS A TEST OF THE LOOPBACK DEVICE\0", bytes1);
  unit_try(OK(xDeviceWrite(0xFFu, &bytes1, data1)));
  unit_try(OK(xMemFree(data1)));
  unit_end();
  unit_begin("xDeviceIsAvailable()");
  unit_try(OK(xDeviceIsAvailable(0xFFu, &res)));
  unit_try(true == res);
  unit_end();
  unit_begin("xDeviceRead()");
  bytes2 = zero;
  data2 = null;
  unit_try(OK(xDeviceRead(0xFFu, &bytes2, &data2)));
  unit_try(0x26u == bytes2);
  unit_try(zero == strncmp((char *) data2, "THIS IS A TEST OF THE LOOPBACK DEVICE\0", bytes2));
  unit_try(OK(xMemFree(data2)));
  unit_end();
  unit_begin("xDeviceSimpleWrite()");
  unit_try(OK(xMemAlloc((volatile Addr_t **) &data3, sizeof(Word_t))));
  *data3 = 0xFAFAu;
  unit_try(OK(xDeviceSimpleWrite(0xFFu, data3)));
  unit_try(OK(xMemFree(data3)));
  unit_end();
  unit_begin("xDeviceSimpleRead()");
  *data4 = zero;
  unit_try(OK(xDeviceSimpleRead(0xFFu, &data4)));
  unit_try(0xFAFAu == *data4);
  unit_try(OK(xMemFree(data4)));
  unit_end();

  return;
}