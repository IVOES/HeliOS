/*UNCRUSTIFY-OFF*/
/**
 * @file device.c
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
#include "device.h"

static DeviceList_t *dlist = null;
static Return_t __DeviceListFind__(const HalfWord_t uid_, Device_t **device_);


Return_t xDeviceRegisterDevice(Return_t (*device_self_register_)()) {
  RET_DEFINE;

  if(NOTNULLPTR(device_self_register_)) {
    /* Call the device driver's DEVICENAME_self_register() function which will
     * in turn call __RegisterDevice__() in this file. */
    if(OK((*device_self_register_)())) {
      RET_OK;
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t __RegisterDevice__(const HalfWord_t uid_, const Byte_t *name_, const DeviceState_t state_, const DeviceMode_t mode_, Return_t (*init_)(
    Device_t *device_), Return_t (*config_)(Device_t *device_, Size_t *size_, Addr_t *config_), Return_t (*read_)(Device_t *device_, Size_t *size_,
  Addr_t **data_), Return_t (*write_)(Device_t *device_, Size_t *size_, Addr_t *data_), Return_t (*simple_read_)(Device_t *device_, Word_t **data_),
  Return_t (*simple_write_)(Device_t *device_, Word_t *data_)) {
  RET_DEFINE;


  Device_t *device = null;
  Device_t *cursor = null;


  if(((zero < uid_) && (NOTNULLPTR(name_)) && (NOTNULLPTR(init_)) && (NOTNULLPTR(config_)) && (NOTNULLPTR(read_)) && (NOTNULLPTR(write_)) && (NOTNULLPTR(
      simple_read_)) && (NOTNULLPTR(simple_write_)) && (NOTNULLPTR(dlist))) || ((zero < uid_) && (NOTNULLPTR(name_)) && (NOTNULLPTR(init_)) && (NOTNULLPTR(
      config_)) && (NOTNULLPTR(read_)) && (NOTNULLPTR(write_)) && (NOTNULLPTR(simple_read_)) && (NOTNULLPTR(simple_write_)) && (NULLPTR(dlist)) && (OK(
      __KernelAllocateMemory__((volatile Addr_t **) &dlist, sizeof(DeviceList_t)))))) {
    if(NOTNULLPTR(dlist)) {
      /* We are expecting *NOT* to find the device UID in the device list. This
       * is to confirm there isn't already a device with the same UID already
       * registered. */
      if(!OK(__DeviceListFind__(uid_, &device))) {
        /* Likewise this should be null since we expected __DeviceListFind__()
         * will *NOT* find a device by that UID. */
        if(NULLPTR(device)) {
          /* Allocate kernel memory for the device structure then if all goes
           * well, populate the structure with all of the device details. */
          if(OK(__KernelAllocateMemory__((volatile Addr_t **) &device, sizeof(Device_t)))) {
            if(NOTNULLPTR(device)) {
              if(OK(__memcpy__(device->name, name_, CONFIG_DEVICE_NAME_BYTES))) {
                device->uid = uid_;
                device->state = state_;
                device->mode = mode_;
                device->bytesWritten = zero;
                device->bytesRead = zero;
                device->available = zero;
                device->init = init_;
                device->config = config_;
                device->read = read_;
                device->write = write_;
                device->simple_read = simple_read_;
                device->simple_write = simple_write_;
                cursor = dlist->head;

                /* If this is the first device added to the device list, then go
                 * ahead and set the device list head to the device. Otherwise
                 * we need to traverse the list until we reach the end. */
                if(NOTNULLPTR(dlist->head)) {
                  while(NOTNULLPTR(cursor->next)) {
                    cursor = cursor->next;
                  }

                  cursor->next = device;
                } else {
                  dlist->head = device;
                }

                dlist->length++;
                RET_OK;
              } else {
                ASSERT;


                /* Because the __memcpy__() failed, we need to free the kernel
                 * memory occupied by the device. */
                __KernelFreeMemory__(device);
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceIsAvailable(const HalfWord_t uid_, Base_t *res_) {
  RET_DEFINE;


  Device_t *device = null;


  if((zero < uid_) && NOTNULLPTR(res_) && (NOTNULLPTR(dlist))) {
    if(OK(__DeviceListFind__(uid_, &device))) {
      if(NOTNULLPTR(device)) {
        *res_ = device->available;
        RET_OK;
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceSimpleWrite(const HalfWord_t uid_, Word_t *data_) {
  RET_DEFINE;


  Device_t *device = null;
  Word_t *data = null;


  if((zero < uid_) && (NOTNULLPTR(data_)) && (NOTNULLPTR(dlist))) {
    /* First, confirm the data to be written to the device is waiting for us in
     * heap memory. */
    if(OK(__MemoryRegionCheckHeap__(data_, MEMORY_REGION_CHECK_OPTION_W_ADDR))) {
      /* Second, look-up the device by its unique identifier in the device list.
       */
      if(OK(__DeviceListFind__(uid_, &device))) {
        if(NOTNULLPTR(device)) {
          /* Third, let's check to make sure the device is running *AND*
           * writable. */
          if(((DeviceModeReadWrite == device->mode) || (DeviceModeWriteOnly == device->mode)) && (DeviceStateRunning == device->state)) {
            /* Fourth, allocate some kernel memory we will copy the data from
             * the heap into. */
            if(OK(__KernelAllocateMemory__((volatile Addr_t **) &data, sizeof(Word_t)))) {
              if(NOTNULLPTR(data)) {
                /* Copy the data from the heap into the kernel memory then call
                 * the device driver's DEVICENAME_simple_write() function. */
                if(OK(__memcpy__(data, data_, sizeof(Word_t)))) {
                  if(OK((*device->simple_write)(device, data))) {
                    /* Free the kernel memory now that we are done. It is up to
                     * the end-user to free the heap memory the data occupies.
                     */
                    if(OK(__KernelFreeMemory__(data))) {
                      device->bytesWritten += sizeof(Word_t);
                      RET_OK;
                    } else {
                      ASSERT;
                    }
                  } else {
                    ASSERT;


                    /* Because DEVICENAME_simple_write() returned an error, need
                     * to free the kernel memory. */
                    __KernelFreeMemory__(data);
                  }
                } else {
                  ASSERT;


                  /* Because __memcpy__() returned an error, we need to free the
                   * kernel memory. */
                  __KernelFreeMemory__(data);
                }
              } else {
                ASSERT;
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceWrite(const HalfWord_t uid_, Size_t *size_, Addr_t *data_) {
  RET_DEFINE;


  Device_t *device = null;
  Byte_t *data = null;


  if((zero < uid_) && (NOTNULLPTR(size_)) && (zero < *size_) && (NOTNULLPTR(data_)) && NOTNULLPTR(dlist)) {
    /* First, confirm the data to be written to the device is waiting for us in
     * heap memory. */
    if(OK(__MemoryRegionCheckHeap__(data_, MEMORY_REGION_CHECK_OPTION_W_ADDR))) {
      /* Second, look-up the device by its unique identifier in the device list.
       */
      if(OK(__DeviceListFind__(uid_, &device))) {
        if(NOTNULLPTR(device)) {
          /* Third, let's check to make sure the device is running *AND*
           * writable. */
          if(((DeviceModeReadWrite == device->mode) || (DeviceModeWriteOnly == device->mode)) && (DeviceStateRunning == device->state)) {
            /* Fourth, allocate some kernel memory we will copy the data from
             * the heap into. */
            if(OK(__KernelAllocateMemory__((volatile Addr_t **) &data, *size_))) {
              if(NOTNULLPTR(data)) {
                /* Copy the data from the heap into the kernel memory then call
                 * the device driver's DEVICENAME_write() function. */
                if(OK(__memcpy__(data, data_, *size_))) {
                  if(OK((*device->write)(device, size_, data))) {
                    /* Free the kernel memory now that we are done. It is up to
                     * the end-user to free the heap memory the data occupies.
                     */
                    if(OK(__KernelFreeMemory__(data))) {
                      device->bytesWritten += *size_;
                      RET_OK;
                    } else {
                      ASSERT;
                    }
                  } else {
                    ASSERT;


                    /* Because DEVICENAME_write() returned an error, we need to
                     * free the kernel memory. */
                    __KernelFreeMemory__(data);
                  }
                } else {
                  ASSERT;


                  /* Because __memcpy__() returned an error, we need to free the
                   * kernel memory. */
                  __KernelFreeMemory__(data);
                }
              } else {
                ASSERT;
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceSimpleRead(const HalfWord_t uid_, Word_t **data_) {
  RET_DEFINE;


  Device_t *device = null;
  Word_t *data = null;


  if((zero < uid_) && NOTNULLPTR(data_) && NOTNULLPTR(dlist)) {
    /* First, look-up the device by its unique identifier in the device list.
     */
    if(OK(__DeviceListFind__(uid_, &device))) {
      if(NOTNULLPTR(device)) {
        /* Second, let's check to make sure the device is running *AND*
         * readable. */
        if(((DeviceModeReadWrite == device->mode) || (DeviceModeReadOnly == device->mode)) && (DeviceStateRunning == device->state)) {
          /* Third, call the device driver's DEVICENAME_simple_read() function
           * and check that the data returned by the device driver is waiting
           * for us in kernel memory. */
          if(OK((*device->simple_read)(device, &data))) {
            if(NOTNULLPTR(data)) {
              if(OK(__MemoryRegionCheckKernel__(data, MEMORY_REGION_CHECK_OPTION_W_ADDR))) {
                /* Allocate the same amount of heap memory to copy the data from
                 * kernel memory into. */
                if(OK(__HeapAllocateMemory__((volatile Addr_t **) data_, sizeof(Word_t)))) {
                  if(NOTNULLPTR(*data_)) {
                    /* Perform the copy from kernel memory to heap memory. */
                    if(OK(__memcpy__(*data_, data, sizeof(Word_t)))) {
                      /* Free the kernel memory now that we are done. It is up
                       * to the end-user to free the heap memory the data
                       * occupies.
                       */
                      if(OK(__KernelFreeMemory__(data))) {
                        device->bytesRead += sizeof(Word_t);
                        RET_OK;
                      } else {
                        ASSERT;
                      }
                    } else {
                      ASSERT;


                      /* Because __memcpy__() returned an error, we need to free
                       * the kernel memory. */
                      __KernelFreeMemory__(data);


                      /* Because __memcpy__() returned an error, we also need to
                       * free the heap memory. */
                      __HeapFreeMemory__(*data_);
                    }
                  } else {
                    ASSERT;


                    /* Because __HeapAllocateMemory__() returned a null pointer,
                     * we need to free the kernel memory. */
                    __KernelFreeMemory__(data);
                  }
                } else {
                  ASSERT;


                  /* Because __HeapAllocateMemory__() returned an error, we need
                   * to free the kernel memory. */
                  __KernelFreeMemory__(data);
                }
              } else {
                ASSERT;
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceRead(const HalfWord_t uid_, Size_t *size_, Addr_t **data_) {
  RET_DEFINE;


  Device_t *device = null;
  Addr_t *data = null;


  if((zero < uid_) && NOTNULLPTR(size_) && NOTNULLPTR(data_) && NOTNULLPTR(dlist)) {
    /* First, look-up the device by its unique identifier in the device list.
     */
    if(OK(__DeviceListFind__(uid_, &device))) {
      if(NOTNULLPTR(device)) {
        /* Second, let's check to make sure the device is running *AND*
         * readable. */
        if(((DeviceModeReadWrite == device->mode) || (DeviceModeReadOnly == device->mode)) && (DeviceStateRunning == device->state)) {
          /* Third, call the device driver's DEVICENAME_read() function and
           * check that the data returned by the device driver is waiting for us
           * in kernel memory. */
          if(OK((*device->read)(device, size_, &data))) {
            if((zero < *size_) && NOTNULLPTR(data)) {
              if(OK(__MemoryRegionCheckKernel__(data, MEMORY_REGION_CHECK_OPTION_W_ADDR))) {
                /* Allocate the same amount of heap memory to copy the data from
                 * kernel memory into. */
                if(OK(__HeapAllocateMemory__((volatile Addr_t **) data_, *size_))) {
                  if(NOTNULLPTR(*data_)) {
                    /* Perform the copy from kernel memory to heap memory. */
                    if(OK(__memcpy__(*data_, data, *size_))) {
                      /* Free the kernel memory now that we are done. It is up
                       * to the end-user to free the heap memory the data
                       * occupies.
                       */
                      if(OK(__KernelFreeMemory__(data))) {
                        device->bytesRead += *size_;
                        RET_OK;
                      }
                    } else {
                      ASSERT;


                      /* Because __memcpy__() returned an error, we need to free
                       * the kernel memory. */
                      __KernelFreeMemory__(data);


                      /* Because __memcpy__() returned an error, we also need to
                       * free the heap memory. */
                      __HeapFreeMemory__(*data_);
                    }
                  } else {
                    ASSERT;


                    /* Because __HeapAllocateMemory__() returned a null pointer,
                     * we need to free the kernel memory. */
                    __KernelFreeMemory__(data);
                  }
                } else {
                  ASSERT;


                  /* Because __HeapAllocateMemory__() returned an error, we need
                   * to free the kernel memory. */
                  __KernelFreeMemory__(data);
                }
              } else {
                ASSERT;
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


static Return_t __DeviceListFind__(const HalfWord_t uid_, Device_t **device_) {
  RET_DEFINE;


  Device_t *cursor = null;


  if((zero < uid_) && (NOTNULLPTR(device_)) && (NOTNULLPTR(dlist))) {
    cursor = dlist->head;

    while((NOTNULLPTR(cursor)) && (cursor->uid != uid_)) {
      cursor = cursor->next;
    }

    if(NOTNULLPTR(cursor)) {
      *device_ = cursor;
      RET_OK;
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceInitDevice(const HalfWord_t uid_) {
  RET_DEFINE;


  Device_t *device = null;


  if((zero < uid_) && (NOTNULLPTR(dlist))) {
    if(OK(__DeviceListFind__(uid_, &device))) {
      if(NOTNULLPTR(device)) {
        if(OK((*device->init)(device))) {
          RET_OK;
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


Return_t xDeviceConfigDevice(const HalfWord_t uid_, Size_t *size_, Addr_t *config_) {
  RET_DEFINE;


  Device_t *device = null;
  Addr_t *config = null;


  if((zero < uid_) && (zero < *size_) && (NOTNULLPTR(config_)) && (NOTNULLPTR(dlist))) {
    if(OK(__MemoryRegionCheckHeap__(config_, MEMORY_REGION_CHECK_OPTION_W_ADDR))) {
      if(OK(__DeviceListFind__(uid_, &device))) {
        if(NOTNULLPTR(device)) {
          if(OK(__KernelAllocateMemory__((volatile Addr_t **) &config, *size_))) {
            if(NOTNULLPTR(config)) {
              if(OK(__memcpy__(config, config_, *size_))) {
                if(OK((*device->config)(device, size_, config))) {
                  if(OK(__memcpy__(config_, config, *size_))) {
                    if(OK(__KernelFreeMemory__(config))) {
                      RET_OK;
                    } else {
                      ASSERT;
                    }
                  } else {
                    ASSERT;
                  }
                } else {
                  ASSERT;
                }
              } else {
                ASSERT;
              }
            } else {
              ASSERT;
            }
          } else {
            ASSERT;
          }
        } else {
          ASSERT;
        }
      } else {
        ASSERT;
      }
    } else {
      ASSERT;
    }
  } else {
    ASSERT;
  }

  RET_RETURN;
}


#if defined(POSIX_ARCH_OTHER)


  void __DeviceStateClear__(void) {
    dlist = null;

    return;
  }


#endif /* if defined(POSIX_ARCH_OTHER) */