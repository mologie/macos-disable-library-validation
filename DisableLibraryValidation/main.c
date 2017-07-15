//
//  DisableLibraryValidation.c
//  DisableLibraryValidation
//
//  Created by Oliver Kuckertz on 15.07.17.
//  Copyright © 2017 Oliver Kuckertz. All rights reserved.
//

#include <mach/mach_types.h>
#include <sys/types.h>
#include <sys/systm.h>
#include <IOKit/IOLib.h> // for IOLog
#include <i386/proc_reg.h> // for get_cr0/set_cr0

#define dbgprintf(STR, ...) \
    IOLog("DisableLibraryValidation: " STR "\n", ## __VA_ARGS__);

kern_return_t DisableLibraryValidation_start(kmod_info_t * ki, void *d);
kern_return_t DisableLibraryValidation_stop(kmod_info_t *ki, void *d);

int	cs_require_lv(struct proc *);

static const uint8_t patch[] = { 0x48, 0x31, 0xC0 /* XOR RAX,RAX */, 0xC3 /* RET */ };
static uint8_t backup[sizeof(patch)];

static
int cli(void)
{
    unsigned long flags;
    asm volatile ("pushf; pop %0; cli;" : "=r" (flags));
    return !!(flags & EFL_IF);
}

static
void sti(void)
{
    asm volatile ("sti; nop;");
}

kern_return_t DisableLibraryValidation_start(kmod_info_t * ki, void *d)
{
    dbgprintf("disabling library validation");

    // disable interrupts and kernel write protection
    int intrflag = cli();
    uintptr_t cr0 = get_cr0();
    set_cr0(cr0 & ~CR0_WP);

    // replace code
    memcpy(backup, (void *)cs_require_lv, sizeof(patch));
    memcpy((void *)cs_require_lv, patch, sizeof(patch));

    // enable kernel write protection and interrupts
    set_cr0(cr0);
    if (intrflag)
        sti();

    // validate result
    if (cs_require_lv(NULL) == 0) {
        return KERN_SUCCESS;
    }
    else {
        dbgprintf("validation failed (and it's a wonder that your machine has not panicked)");
        return KERN_FAILURE;
    }
}

kern_return_t DisableLibraryValidation_stop(kmod_info_t *ki, void *d)
{
    dbgprintf("enabling library validation (unload)");

    // disable interrupts and kernel write protection
    int intrflag = cli();
    uintptr_t cr0 = get_cr0();
    set_cr0(cr0 & ~CR0_WP);

    // replace code
    memcpy((void *)cs_require_lv, backup, sizeof(patch));

    // enable kernel write protection and interrupts
    set_cr0(cr0);
    if (intrflag)
        sti();

    return KERN_SUCCESS;
}
