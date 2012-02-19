#ifndef KERNEL_DRIVER_CONSOLE_CONSOLE_H
#define KERNEL_DRIVER_CONSOLE_CONSOLE_H
#include <stdint.h>

void DRIVER_CONSOLE_Init(uint32_t video_ram_addr, boolean clearScreen);

void DRIVER_CONSOLE_ClearScreen();

void DRIVER_CONSOLE_ClearScreenWithColor(uint8_t color);

boolean DRIVER_CONSOLE_IsVideoMono();

void DRIVER_CONSOLE_GotoXY(int x,int y);

void DRIVER_CONSOLE_PutChar(char ch);

void DRIVER_CONSOLE_PutCharWithColor(char ch, uint8_t color);

void DRIVER_CONSOLE_PutString(const char* str);

void DRIVER_CONSOLE_PutStringWithColor(const char* str, uint16_t color);

#endif
