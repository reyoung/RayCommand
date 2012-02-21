//! inline的汇编代码，可以在C中写一些汇编语句
//! \note 参考自 http://wiki.osdev.org/Inline_Assembly。包括GCC的嵌入汇编语法，这篇文章中都有很好的介绍。

#ifndef BASECRT_INLINEASM_H
#define BASECRT_INLINEASM_H
#include <stdint.h>

#define outb(Port,Value)\
	__asm__("outb %%al,%%dx;"::"d"(Port),"a"(Value))

#define outw(Port,Value)\
	__asm__("outw %%ax,%%dx;"::"d"(Port),"a"(Value))

static inline
uint8_t inb( uint16_t port )
{
    uint8_t ret;
    __asm__ volatile( "inb %1, %0"
                  : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline 
uint16_t inw(uint16_t port){
	uint16_t ret;
	__asm__ volatile("inw %1, %0":
			"=a"(ret):
			"Nd"(port));
		return ret;
}



#endif
