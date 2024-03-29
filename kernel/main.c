#include "driver/console/console.h"
#include "driver/X86_arch/GDT.h"
#include "driver/X86_arch/IDT.h"
#include "driver/X86_arch/ISR.h"

//! 初始化工作
static void Initialize();

//! 控制台的初始化
static void InitializeConsole();

//! Architecture Special Initialize
static void InitializeArchitectureSpecials();

static void DivByZeroCallback(struct DRIVER_X86_InterruptRegs* reg){
	DRIVER_CONSOLE_PutString("ISR Test Correct!\r\n");
	for(;;);
}


void kmain(void* mbd,unsigned int magic){
	if(magic != 0x2BADB002 ){
		//! Handle Error
	}

	Initialize();

	DRIVER_CONSOLE_SetColor(0x0a);
	DRIVER_CONSOLE_ClearScreen();
	DRIVER_CONSOLE_PutString("Hello world!\r\n");
	DRIVER_X86_InstallISRCallback(0,DivByZeroCallback);

	int a=0;
	a/=a;
}


static void Initialize(){
	InitializeArchitectureSpecials();
	InitializeConsole();
}

static void InitializeConsole(){
	if(DRIVER_CONSOLE_IsVideoMono()){	//! 如果是单色显示器
		DRIVER_CONSOLE_Init(0xB0000,True);
	} else {
		DRIVER_CONSOLE_Init(0xB8000,True);
	}
}
static void InitializeArchitectureSpecials(){
	DRIVER_X86_SetupGDT();
	DRIVER_X86_SetupIDT();
}

