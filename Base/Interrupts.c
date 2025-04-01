#pragma region LICENSE

// MIT License
//
// Copyright (c) 2025 Rohan Bharatia
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma endregion LICENSE

#ifndef _CORE_BASE_INTERRUPTS_C_
    #define _CORE_BASE_INTERRUPTS_C_

#include "Interrupts.h"

static InterruptHandler interruptHandlers[MAX_INTERRUPTS] = { NULL };
static uint8 interruptModes[MAX_INTERRUPTS]               = { 0 };

void attachInterrupt(uint8 pin, InterruptHandler handler, uint8 mode)
{
    if (pin < MAX_INTERRUPTS)
    {
        interruptHandlers[pin] = handler;
        interruptModes[pin]    = mode;
    }
}

void detachInterrupt(uint8 pin)
{
    if (pin < MAX_INTERRUPTS)
    {
        interruptHandlers[pin] = NULL;
        interruptModes[pin]    = 0;
    }
}

void noInterrupts(void)
{
    // Disable interrupts in hardware
    asm volatile("cli");
}

void interrupts(void)
{
    // Enable interrupts in hardware
#ifdef __x86_64__
    asm volatile("sti");
#elif defined(__i386__)
    asm volatile("sti");
#elif defined(__arm__)
    asm volatile("cpsie i");
#elif defined(__aarch64__)
    asm volatile("msr daifclr, #2");
#elif defined(__riscv)
    asm volatile("csrw mie, zero");
#elif defined(__powerpc__)
    asm volatile("mtsrin mcsr, 0x100");
#elif defined(__mips__)
    asm volatile("mfc0 $1, $12");
    asm volatile("ori $1, $1, 0x2000");
    asm volatile("mtc0 $1, $12");
#elif defined(__sparc__)
    asm volatile("wrpr %g0, 0x100");
#elif defined(__avr__)
    asm volatile("sei");
#elif defined(__msp430__)
    asm volatile("bic #0x0001, SR");
#elif defined(__stm32__)
    asm volatile("cpsie i");
#elif defined(__pic32__)
    asm volatile("cpsie i");
#elif defined(__blackfin__)
    asm volatile("enable i");
#elif defined(__sh__)
    asm volatile("sts SR, 0x100");
#elif defined(__nios2__)
    asm volatile("enable i");
#elif defined(__microblaze__)
    asm volatile("msr msr_int, 1");
#elif defined(__openrisc__)
    asm volatile("l.mfspr r0, 0x100");
    asm volatile("ori r0, r0, 0x100");
    asm volatile("l.mtspr 0x100, r0");
#elif defined(__epiphany__)
    asm volatile("enable i");
#elif defined(__arc__)
    asm volatile("sts SR, 0x100");
#elif defined(__xtensa__)
    asm volatile("wsr.uncached icount, 0");
#elif defined(__nios__)
    asm volatile("enable i");
#elif defined(__or1k__)
    asm volatile("l.mfspr r0, 0x100");
    asm volatile("ori r0, r0, 0x100");
    asm volatile("l.mtspr 0x100, r0");
#elif defined(__c6x__)
    asm volatile("sts SR, 0x100");
#elif defined(__tms320c6x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c54x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c55x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c62x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c64x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c67x__)
    asm volatile("sts SR, 0x100");
#elif defined(__c674x__)
    asm volatile("sts SR, 0x100");
#else /* (NOT) __x86_64__, defined(__i386__), defined(__arm__), defined(__aarch64__),
               defined(__riscv), defined(__powerpc__), defined(__mips__), defined(__sparc__),
               defined(__avr__), defined(__msp430__), defined(__stm32__), defined(__pic32__),
               defined(__blackfin__), defined(__sh__), defined(__nios2__), defined(__microblaze__),
               defined(__openrisc__), defined(__epiphany__), defined(__arc__), defined(__xtensa__),
               defined(__nios__), defined(__or1k__), defined(__c6x__), defined(__tms320c6x__),
               defined(__c54x__), defined(__c55x__), defined(__c62x__), defined(__c64x__),
               defined(__c67x__), defined(__c674x__) */
    #error Unsupported architecture!
#endif /* __x86_64__, defined(__i386__), defined(__arm__), defined(__aarch64__),
          defined(__riscv), defined(__powerpc__), defined(__mips__), defined(__sparc__),
          defined(__avr__), defined(__msp430__), defined(__stm32__), defined(__pic32__),
          defined(__blackfin__), defined(__sh__), defined(__nios2__), defined(__microblaze__),
          defined(__openrisc__), defined(__epiphany__), defined(__arc__), defined(__xtensa__),
          defined(__nios__), defined(__or1k__), defined(__c6x__), defined(__tms320c6x__),
          defined(__c54x__), defined(__c55x__), defined(__c62x__), defined(__c64x__),
          defined(__c67x__), defined(__c674x__) */
}

#endif // _CORE_BASE_INTERRUPTS_C_
