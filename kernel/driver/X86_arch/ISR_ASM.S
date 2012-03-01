extern _fault_handler

%macro DEFINE_ISR_WITHOUT_PARAM 1
global  _isr%1
_isr%1:
	cli
	push byte 0
	push byte %1
	jmp  isr_common_stub
%endmacro

%macro DEFINE_ISR_WITH_PARAM 1
global _isr%1
_isr%1:
	cli
	push byte %1
	jmp  isr_common_stub
%endmacro




DEFINE_ISR_WITHOUT_PARAM 0
DEFINE_ISR_WITHOUT_PARAM 1
DEFINE_ISR_WITHOUT_PARAM 2
DEFINE_ISR_WITHOUT_PARAM 3
DEFINE_ISR_WITHOUT_PARAM 4
DEFINE_ISR_WITHOUT_PARAM 5
DEFINE_ISR_WITHOUT_PARAM 6
DEFINE_ISR_WITHOUT_PARAM 7
DEFINE_ISR_WITH_PARAM 8
DEFINE_ISR_WITHOUT_PARAM 9
DEFINE_ISR_WITH_PARAM 10
DEFINE_ISR_WITH_PARAM 11
DEFINE_ISR_WITH_PARAM 12
DEFINE_ISR_WITH_PARAM 13
DEFINE_ISR_WITH_PARAM 14
%assign i 15
%rep 32-15
	DEFINE_ISR_WITH_PARAM i
%assign i i+1
%endrep



isr_common_stub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov  ax,0x10
	mov  ds,ax
	mov es, ax
	mov fs, ax
   	mov gs, ax
	mov eax, esp   ; Push us the stack
	push eax
	mov eax, _fault_handler
	call eax       ; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

	
