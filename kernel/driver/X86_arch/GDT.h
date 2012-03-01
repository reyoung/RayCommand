#ifndef KERNEL_DRIVER_X86ARCH_GDT_H
#define KERNEL_DRIVER_X86ARCH_GDT_H
#include <stdint.h>

struct DRIVER_X86_GDTEntry{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_middle;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  base_high;
} __attribute__((packed)) ;


struct DRIVER_X86_GDTPtr{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern struct DRIVER_X86_GDTEntry gdt[3];

extern struct DRIVER_X86_GDTPtr  gdt_pointer;

extern void gdt_flush();

extern void DRIVER_X86_SetupGDT();

#endif
