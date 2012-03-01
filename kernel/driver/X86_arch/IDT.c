#include "IDT.h"

struct DRIVER_X86_IDTEntry idt[256];

static void idt_set_gate(uint8_t num,uint32_t base,uint16_t sel,uint8_t flags){
	idt[num].base_lo = (base&0xffff);
	idt[num].base_hi = (base>>16)&0xffff;
	idt[num].sel = sel;
	idt[num].flags = flags;
	idt[num].always0 = 0;	
}
//extern void __IDT_

static inline
void lidt( void * base, unsigned int size )
{
    unsigned int i[2];
 
    i[0] = size << 16;
    i[1] = (unsigned int)base;
    __asm( "lidt (%0)"
         : : "p"(((char *) i)+2) );
}

void DRIVER_X86_SetupIDT(){
	lidt(&idt,(sizeof (struct DRIVER_X86_IDTEntry) * 256) - 1);
}
