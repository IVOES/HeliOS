/*UNCRUSTIFY-OFF*/
/**
 * @file device.h
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief Kernel source code for device drivers
 * @version 0.4.0
 * @date 2022-09-01
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
#ifndef DEVICE_H_
  #define DEVICE_H_

  #include "config.h"
  #include "defines.h"
  #include "types.h"
  #include "port.h"
  #include "mem.h"
  #include "queue.h"
  #include "stream.h"
  #include "sys.h"
  #include "task.h"
  #include "timer.h"

  #ifdef __cplusplus
    extern "C" {
  #endif /* ifdef __cplusplus */
  Return_t xDeviceRegisterDevice(Return_t (*device_self_register_)());
  Return_t __RegisterDevice__(const HalfWord_t uid_, const Byte_t *name_, const DeviceState_t state_, const DeviceMode_t mode_, Return_t (*init_)(
      Device_t *device_), Return_t (*config_)(Device_t *device_, Size_t *size_, Addr_t *config_), Return_t (*read_)(Device_t *device_, Size_t *size_,
    Addr_t **data_), Return_t (*write_)(Device_t *device_, Size_t *size_, Addr_t *data_), Return_t (*simple_read_)(Device_t *device_, Word_t **data_),
    Return_t (*simple_write_)(Device_t *device_, Word_t *data_));
  Return_t xDeviceIsAvailable(const HalfWord_t uid_, Base_t *res_);
  Return_t xDeviceSimpleWrite(const HalfWord_t uid_, Word_t *data_);
  Return_t xDeviceWrite(const HalfWord_t uid_, Size_t *size_, Addr_t *data_);
  Return_t xDeviceSimpleRead(const HalfWord_t uid_, Word_t **data_);
  Return_t xDeviceRead(const HalfWord_t uid_, Size_t *size_, Addr_t **data_);
  Return_t xDeviceInitDevice(const HalfWord_t uid_);
  Return_t xDeviceConfigDevice(const HalfWord_t uid_, Size_t *size_, Addr_t *config_);

  #if defined(POSIX_ARCH_OTHER)
    void __DeviceStateClear__(void);
  #endif /* if defined(POSIX_ARCH_OTHER) */

  #ifdef __cplusplus
    }
  #endif /* ifdef __cplusplus */
#endif /* ifndef DEVICE_H_ */