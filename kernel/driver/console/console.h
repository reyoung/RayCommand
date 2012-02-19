#ifndef KERNEL_DRIVER_CONSOLE_CONSOLE_H
#define KERNEL_DRIVER_CONSOLE_CONSOLE_H
#include <stdint.h>

void DRIVER_CONSOLE_Init(uint32_t video_ram_addr, boolean clearScreen);

void DRIVER_CONSOLE_ClearScreen();

void DRIVER_CONSOLE_ClearScreenWithColor(uint8_t color);

boolean DRIVER_CONSOLE_IsVideoMono();

#endif
