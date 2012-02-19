#include "driver/console/console.h"

void kmain(void* mbd,unsigned int magic){
	if(magic != 0x2BADB002 ){
		//! Handle Error
	}

	DRIVER_CONSOLE_Init(0xb8000,True);

	DRIVER_CONSOLE_PutString("Hello world!\r\n");
}
