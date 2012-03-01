#ifndef KERNEL_DRIVER_X86ARCH_IDT_H
#define KERNEL_DRIVER_X86ARCH_IDT_H
#include <stdint.h>
struct DRIVER_X86_IDTEntry{
	uint16_t base_lo;
	uint16_t sel;
	uint8_t  always0;
	uint8_t  flags;
	uint16_t base_hi;
} __attribute__((packed));

struct DRIVER_X86_IDTPtr{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern struct DRIVER_X86_IDTEntry idt[256];
extern struct DRIVER_X86_IDTPtr   idtp;



void DRIVER_X86_SetupIDT();


#endif
