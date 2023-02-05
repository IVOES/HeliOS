/*UNCRUSTIFY-OFF*/
/**
 * @file memory_harness.c
 * @author Manny Peterson (mannymsp@gmail.com)
 * @brief
 * @version 0.4.0
 * @date 2022-08-27
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
#include "memory_harness.h"

static Size_t sizes[0x20u] = {
  0x2532u, 0x1832u, 0x132u, 0x2932u, 0x332u, 0x1432u, 0x1332u, 0x532u, 0x1732u, 0x932u, 0x1432u, 0x2232u, 0x1432u, 0x3132u, 0x032u, 0x1132u, 0x632u, 0x932u, 0x1532u, 0x632u, 0x1832u, 0x132u, 0x1332u, 0x3132u, 0x2732u, 0x1532u, 0x2432u, 0x2932u, 0x2432u, 0x2932u, 0x3032u, 0x2332u
};
static Size_t order[0x20u] = {
  0x02u, 0x16u, 0x07u, 0x0Cu, 0x06u, 0x00u, 0x0Du, 0x18u, 0x10u, 0x08u, 0x0Au, 0x1Eu, 0x0Bu, 0x0Eu, 0x03u, 0x09u, 0x19u, 0x05u, 0x1Cu, 0x1Du, 0x0Fu, 0x01u, 0x1Au, 0x04u, 0x13u, 0x11u, 0x1Fu, 0x12u, 0x17u, 0x15u, 0x14u, 0x1Bu
};
static MemoryTest_t tests[0x20u];


void memory_harness(void) {
  Size_t i;
  Size_t used;
  Size_t actual;
  Base_t *mem01;
  MemoryRegionStats_t *mem02;
  MemoryRegionStats_t *mem03;
  Task_t *mem04 = NULL;
  Byte_t *mem05 = NULL;


  unit_begin("Unit test for memory region defragmentation routine");
  i = zero;
  used = zero;
  actual = zero;

  for(i = 0; i < 0x20u; i++) {
    tests[i].size = sizes[i];
    tests[i].blocks = (sizes[i] / CONFIG_MEMORY_REGION_BLOCK_SIZE) + 1; /* ... + 1; Assuming a memory region entry only takes one (1) block - that may not always be true. */

    if(zero < ((Size_t) (sizes[i] % CONFIG_MEMORY_REGION_BLOCK_SIZE))) {
      tests[i].blocks += 1;
    }

    unit_try(ISSUCCESSFUL(xMemAlloc((volatile Addr_t **) &tests[i].ptr, sizes[i])));
    unit_try(NULL != tests[i].ptr);
    used += tests[i].blocks * CONFIG_MEMORY_REGION_BLOCK_SIZE;
    unit_try(ISSUCCESSFUL(xMemGetUsed(&actual)));
    unit_try(used == actual);
    unit_try(ISSUCCESSFUL(xMemGetSize(tests[i].ptr, &actual)));
    unit_try((tests[i].blocks * CONFIG_MEMORY_REGION_BLOCK_SIZE) == actual);
  }

  unit_try(!ISSUCCESSFUL(xMemAlloc((volatile Addr_t **) &mem05, 0x99999u)));

  for(i = 0; i < 0x20u; i++) {
    unit_try(ISSUCCESSFUL(xMemFree(tests[order[i]].ptr)));
  }

  unit_try(ISSUCCESSFUL(xMemGetUsed(&actual)));
  unit_try(0x0u == actual);
  unit_try(ISSUCCESSFUL(xMemAlloc((volatile Addr_t **) &mem05, (CONFIG_MEMORY_REGION_SIZE_IN_BLOCKS - 1) * CONFIG_MEMORY_REGION_BLOCK_SIZE)));
  actual = zero;
  unit_try(ISSUCCESSFUL(xMemGetUsed(&actual)));
  unit_try((CONFIG_MEMORY_REGION_SIZE_IN_BLOCKS * CONFIG_MEMORY_REGION_BLOCK_SIZE) == actual);
  unit_try(ISSUCCESSFUL(xMemFree(mem05)));
  unit_end();
  unit_begin("xMemAlloc()");
  mem01 = NULL;
  unit_try(ISSUCCESSFUL(xMemAlloc((volatile Addr_t **) &mem01, 0x32000u)));
  unit_try(NULL != mem01);
  unit_end();
  unit_begin("xMemGetUsed()");
  unit_try(ISSUCCESSFUL(xMemGetUsed(&actual)));
  unit_try(0x32020u == actual);
  unit_end();
  unit_begin("xMemGetSize()");
  unit_try(ISSUCCESSFUL(xMemGetSize(mem01, &actual)));
  unit_try(0x32020u == actual);
  unit_end();
  unit_begin("xMemGetHeapStats()");
  mem02 = NULL;
  unit_try(ISSUCCESSFUL(xMemGetHeapStats(&mem02)));
  unit_try(NULL != mem02);
  unit_try(0x63A0u == mem02->availableSpaceInBytes);
  unit_try(0x63A0u == mem02->largestFreeEntryInBytes);
  unit_try(0x0u == mem02->minimumEverFreeBytesRemaining);
  unit_try(0x31Du == mem02->numberOfFreeBlocks);
  unit_try(0x63A0u == mem02->smallestFreeEntryInBytes);
  unit_try(0x23u == mem02->successfulAllocations);
  unit_try(0x21u == mem02->successfulFrees);
  unit_end();
  unit_begin("xMemGetKernelStats()");
  mem03 = NULL;
  mem04 = NULL;
  mem04 = xTaskCreate((Char_t *) "NONE", memory_harness_task, NULL);
  unit_try(NULL != mem04);
  xTaskDelete(mem04);
  unit_try(ISSUCCESSFUL(xMemGetKernelStats(&mem03)));
  unit_try(NULL != mem03);
  unit_try(0x383C0u == mem03->availableSpaceInBytes);
  unit_try(0x383C0u == mem03->largestFreeEntryInBytes);
  unit_try(0x38340u == mem03->minimumEverFreeBytesRemaining);
  unit_try(0x1C1Eu == mem03->numberOfFreeBlocks);
  unit_try(0x383C0u == mem03->smallestFreeEntryInBytes);
  unit_try(0x2u == mem03->successfulAllocations);
  unit_try(0x1u == mem03->successfulFrees);
  unit_try(ISSUCCESSFUL(xMemFree(mem01)));
  unit_try(ISSUCCESSFUL(xMemFree(mem02)));
  unit_try(ISSUCCESSFUL(xMemFree(mem03)));
  unit_end();

  return;
}


void memory_harness_task(Task_t *task_, TaskParm_t *parm_) {
  xTaskSuspendAll();

  return;
}