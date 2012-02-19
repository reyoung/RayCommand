#include "console.h"

static uint8_t Color = 0x07;
static char* VideoRam = 0xb8000;
static uint8_t X=0;
static uint8_t Y=0;
#define LINE_COUNT 25
#define COLUMN_COUNT 80


void DRIVER_CONSOLE_Init(uint32_t video_ram_addr, boolean clearScreen){
	VideoRam = (char *)video_ram_addr;
	if(clearScreen){
		DRIVER_CONSOLE_ClearScreen();
	}
}

void DRIVER_CONSOLE_ClearScreen(){
	DRIVER_CONSOLE_ClearScreenWithColor(Color);
}

void DRIVER_CONSOLE_ClearScreenWithColor(uint8_t color){
	int i=0;
	X=0;
	Y=0;
	if(DRIVER_CONSOLE_IsVideoMono()){
		for(i=0;i<LINE_COUNT * COLUMN_COUNT; ++i){
			VideoRam[i]=' ';
		}
	} else {
		for(i=0;i< LINE_COUNT * COLUMN_COUNT; ++i){
			VideoRam[i*2]=' ';
			VideoRam[i*2+1] = color;
		}
	}
}

boolean DRIVER_CONSOLE_IsVideoMono(){
	char c = (*(volatile uint16_t*)0x410)&0x30;
	return (c==0x30);
}

