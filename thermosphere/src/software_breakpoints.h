/*
 * Copyright (c) 2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define _REENT_ONLY
#include <errno.h>

#include "spinlock.h"

#define MAX_SW_BREAKPOINTS  32

typedef struct SoftwareBreakpoint {
    u64 address; // VA
    u32 savedInstruction;
    u32 uid;
    bool persistent;
    bool applied;
} SoftwareBreakpoint;

typedef struct SoftwareBreakpointManager {
    RecursiveSpinlock lock;
    size_t numBreakpoints;
    SoftwareBreakpoint breakpoints[MAX_SW_BREAKPOINTS];
    u32 bpUniqueCounter;
} SoftwareBreakpointManager;

extern SoftwareBreakpointManager g_softwareBreakpointManager;

bool revertAllSoftwareBreakpoints(void);
bool applyAllSoftwareBreakpoints(void);

int addSoftwareBreakpoint(u64 addr, bool persistent);
int removeSoftwareBreakpoint(u64 addr, bool keepPersistent);
int removeAllSoftwareBreakpoints(bool keepPersistent);