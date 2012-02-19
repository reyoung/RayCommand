#include "console.h"
#include <InlineAsm.h>
static uint8_t Color = 0x07;
static char* VideoRam = 0xb8000;
static uint16_t X=0;
static uint16_t Y=0;

#define LINE_COUNT 25
#define COLUMN_COUNT 80


static inline void __UpdateCursorPosition(){
	uint16_t pos = (Y*80)+X;
	outb(0x3D4,0x0F);
	outb(0x3D5,(uint8_t)(pos&0xFF));
	outb(0x3D4,0x0E);
	outb(0x3D5,(uint8_t)((pos>>8)&0xFF));
}

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
	__UpdateCursorPosition();
}

boolean DRIVER_CONSOLE_IsVideoMono(){
	char c = (*(volatile uint16_t*)0x410)&0x30;
	return (c==0x30);
}

void DRIVER_CONSOLE_GotoXY(int x,int y){
	X=x;
	Y=y;
	__UpdateCursorPosition();
}

void DRIVER_CONSOLE_PutChar(char ch){
	DRIVER_CONSOLE_PutCharWithColor(ch,Color);
}

void DRIVER_CONSOLE_PutCharWithColor(char ch,uint8_t color){
	switch(ch){
		case '\t':
		case '\n':
			++Y;
			//! Scroll Up Detective;
			if(Y>LINE_COUNT){
				DRIVER_CONSOLE_ClearScreen();
			}
			break;
		case '\r':
			X=0;
			break;
		default:
			if(DRIVER_CONSOLE_IsVideoMono()) {
				VideoRam[Y*80+X]=ch;
			} else {
				volatile uint16_t* where;
				where=(uint16_t*)(VideoRam)+(Y*80+X);
				*where=ch| (((uint16_t)color)<<8);
			}
			++X;
			if(X>COLUMN_COUNT){
				X=0;
				++Y;
				if(Y>LINE_COUNT){
					//! Scroll Up. Currently ClearScreen
					DRIVER_CONSOLE_ClearScreen();
				}
			}
	}
	__UpdateCursorPosition();
}

void DRIVER_CONSOLE_PutString(const char* str){
	DRIVER_CONSOLE_PutStringWithColor(str,Color);
}

void DRIVER_CONSOLE_PutStringWithColor(const char* str, uint16_t color){
	char* temp = str;
	while(*temp){
		DRIVER_CONSOLE_PutCharWithColor(*temp,color);
		++temp;
	}
}
