/*
 * HeliOS Embedded Operating System
 * Copyright (C) 2020 Manny Peterson <me@mannypeterson.com>
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
 */

#include "HeliOS.h"
#include "list.h"
#include "mem.h"
#include "task.h"
#include "timer.h"

volatile TaskListItem *taskListHead;
volatile TaskListItem *taskListTail;
volatile TaskListItem *taskListPrev;
volatile TaskListItem *taskListCurr;

void TaskListInit() {
  taskListHead = NULL;
  taskListTail = NULL;
  taskListPrev = NULL;
  taskListCurr = NULL;
  TaskListRewind();
}

void TaskListClear() {
  while (taskListHead)
    TaskListRemove();
}

void TaskListAdd(Task *task_) {
  TaskListItem *item = (TaskListItem *)xMemAlloc(sizeof(TaskListItem));

  if (item && task_) {
    item->task = task_;
    item->next = NULL;
    if (taskListHead) {
      taskListTail->next = item;
      taskListTail = item;
      TaskListRewind();
    } else {
      taskListHead = item;
      taskListTail = item;
      TaskListRewind();
    }
  }
}

void TaskListRemove() {
  if (taskListCurr) {
    if (taskListCurr == taskListHead && taskListCurr == taskListTail) {
      TaskListItem *item = taskListHead;
      TaskListInit();
      xMemFree(item->task);
      xMemFree(item);
    } else if (taskListCurr == taskListHead) {
      TaskListItem *item = taskListHead;
      taskListHead = taskListHead->next;
      TaskListRewind();
      xMemFree(item->task);
      xMemFree(item);
    } else if (taskListCurr == taskListTail) {
      TaskListItem *item = taskListTail;
      taskListTail = taskListPrev;
      taskListPrev->next = NULL;
      TaskListRewind();
      xMemFree(item->task);
      xMemFree(item);
    } else {
      TaskListItem *item = taskListCurr;
      taskListPrev->next = taskListCurr->next;
      TaskListRewind();
      xMemFree(item->task);
      xMemFree(item);
    }
  }
}

Task *TaskListGet() {
  if (taskListCurr)
    return taskListCurr->task;
  return NULL;
}

bool TaskListMoveNext() {
  if (taskListCurr) {
    if (taskListCurr->next) {
      taskListPrev = taskListCurr;
      taskListCurr = taskListCurr->next;
      return true;
    }
  }
  return false;
}

void TaskListRewind() {
  taskListPrev = NULL;
  taskListCurr = taskListHead;
}
