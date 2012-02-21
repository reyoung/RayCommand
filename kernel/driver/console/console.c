#include "console.h"
#include <InlineAsm.h>

//! 颜色全局变量，灰底白字
static uint8_t Color = 0x07;

//! 显存地址的全局变量，通常情况下是0xB8000，但是也有几种可能性
//! ，在初始化函数中，有显存地址的选择
static char* VideoRam = (char *)0xb8000;

//! 当前的光标所在的位置，内部存储。
static uint16_t X=0;
static uint16_t Y=0;

//! Mode 3h中line和column为80*25
#define LINE_COUNT 25
#define COLUMN_COUNT 80

//! 将屏幕上的光标移动到内部保存的X,Y位置
//! \note 参考自 http://wiki.osdev.org/Text_Mode_Cursor#Moving_the_Cursor_without_the_BIOS
//!       向0x3D4这个地址输出X,Y值即可。
//! \todo 0x3D4这个地址，应该向BIOS中查询，但是大多数计算机地址均为0x3D4
static void __UpdateCursorPosition(){
	uint16_t pos = (Y*80)+X;
	outb(0x3D4,0x0F);	//! 对应outb汇编指令，Intel风格而非ANSI风格
	outb(0x3D5,(uint8_t)(pos&0xFF));
	outb(0x3D4,0x0E);
	outb(0x3D5,(uint8_t)((pos>>8)&0xFF));
}

//! 初始化屏幕，重点在传入的显存地址
void DRIVER_CONSOLE_Init(uint32_t video_ram_addr, boolean clearScreen){
	VideoRam = (char *)video_ram_addr;
	if(clearScreen){
		DRIVER_CONSOLE_ClearScreen();
	}
}

//! 使用内部颜色清屏
void DRIVER_CONSOLE_ClearScreen(){
	DRIVER_CONSOLE_ClearScreenWithColor(Color);
}

//! 清屏，即向屏幕上输出整屏幕的空格
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

//! 判断显示器或当前显示模式是否为单色
//! \note 参考自http://wiki.osdev.org/Detecting_Colour_and_Monochrome_Monitors
//        如果是单色显示，在输出的时候，有一定的区别。大部分情况下，是彩色的。
boolean DRIVER_CONSOLE_IsVideoMono(){
	char c = (*(volatile uint16_t*)0x410)&0x30;
	return (c==0x30);
}

//! 将光标移动到X,Y。首先更新X，Y的内部状态，其次调用__UpdateCursorPosition函数
void DRIVER_CONSOLE_GotoXY(int x,int y){
	X=x;
	Y=y;
	__UpdateCursorPosition();
}

//! 输出字符，并且光标后移
void DRIVER_CONSOLE_PutChar(char ch){
	DRIVER_CONSOLE_PutCharWithColor(ch,Color);
}

//! 输出一个字符的实现，default中为默认情况，其他均为特殊的空白符
void DRIVER_CONSOLE_PutCharWithColor(char ch,uint8_t color){
	switch(ch){
		case '\t':
			DRIVER_CONSOLE_PutCharWithColor(' ',color);
			DRIVER_CONSOLE_PutCharWithColor(' ',color);
			DRIVER_CONSOLE_PutCharWithColor(' ',color);
			DRIVER_CONSOLE_PutCharWithColor(' ',color);
			break;
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

//! 输出字符串
void DRIVER_CONSOLE_PutString(const char* str){
	DRIVER_CONSOLE_PutStringWithColor(str,Color);
}

//! 输出字符串
//! \todo 优化，从而不调用PutCharWithColor，这样子可以最后的时候一起移动光标
void DRIVER_CONSOLE_PutStringWithColor(const char* str, uint16_t color){
	const char* temp = str;
	while(*temp){
		DRIVER_CONSOLE_PutCharWithColor(*temp,color);
		++temp;
	}
}

void DRIVER_CONSOLE_SetColor(uint8_t color){
	Color = color;
}

uint16_t DRIVER_CONSOLE_GetColor(){
	return Color;
}


//! 设置某一位置的字符，光标不移动！
void DRIVER_CONSOLE_SetChar(char ch,int16_t x, int16_t y){
	DRIVER_CONSOLE_SetCharWithColor(ch,x,y,Color);
}

//! 设置某一位置的字符，光标不移动！
void DRIVER_CONSOLE_SetCharWithColor(char ch, int16_t x,int16_t y, int8_t color){
	if(DRIVER_CONSOLE_IsVideoMono()) {
		VideoRam[y*80+x]=ch;
	} else {
		volatile uint16_t* where;
		where=(uint16_t*)(VideoRam)+(y*80+x);
		*where=ch| (((uint16_t)color)<<8);
	}
}


