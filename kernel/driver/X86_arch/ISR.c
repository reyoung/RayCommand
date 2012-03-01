#include "ISR.h"
#include "../console/console.h"
#include "IDT.h"

static const char * ErrorMessage[]={
"Division By Zero Exception",
"Debug Exception",
"Non Maskable Interrupt Exception",
"Breakpoint Exception",
"Into Detected Overflow Exception",
"Out of Bounds Exception",
"Invalid Opcode Exception",
"No Coprocessor Exception",
"Double Fault Exception",
"Coprocessor Segment Overrun Exception",
"Bad TSS Exception",
"Segment Not Present Exception",
"Stack Fault Exception",
"General Protection Fault Exception",
"Page Fault Exception",
"Unknown Interrupt Exception",
"Coprocessor Fault Exception",
"Alignment Check Exception (486+)",
"Machine Check Exception (Pentium/586+)",
"Reserved Exceptions"
};


typedef void (*CallbackType)(struct DRIVER_X86_InterruptRegs*);

static CallbackType functions[32]={
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
};

void DRIVER_X86_InstallISRCallback(int int_no, void(*func)(struct DRIVER_X86_InterruptRegs* )){
	if(int_no<32&&int_no>=0)
		functions[int_no]=func;
}

void* DRIVER_X86_GetISRCallback(int int_no){
	return functions[int_no];
}


/* This defines what the stack looks like after an ISR was running */
void _fault_handler(struct DRIVER_X86_InterruptRegs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        if(DRIVER_X86_GetISRCallback(r->int_no)){
		functions[r->int_no](r);
	}else{
		DRIVER_CONSOLE_PutString(r->int_no>18?ErrorMessage[19]:ErrorMessage[r->int_no]);
        	DRIVER_CONSOLE_PutString(" Detective!\r\n");
        	for (;;);
	}
    }
}

