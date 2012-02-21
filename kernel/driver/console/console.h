#ifndef KERNEL_DRIVER_CONSOLE_CONSOLE_H
#define KERNEL_DRIVER_CONSOLE_CONSOLE_H

#include <stdint.h>	//! For uint32_t, uint8_t, etc.

//! 初始化Console
//! \param video_ram_addr 当前控制台显存的初始地址
//! \param clearscreen 是否清屏,True的话，初始化时会顺便清屏
void DRIVER_CONSOLE_Init(uint32_t video_ram_addr, boolean clearScreen);

//! 清屏，将屏幕的字符全部清除
//! \note 使用内部维护的颜色
void DRIVER_CONSOLE_ClearScreen();

//! 清屏，使用对应的颜色
//! \param 清屏使用的颜色
void DRIVER_CONSOLE_ClearScreenWithColor(uint8_t color);

//! 判断当前显卡是否是单色的显卡(现代的电脑基本上是False)
//! \return true if mono.
boolean DRIVER_CONSOLE_IsVideoMono();

//! 将光标移动到X,Y
void DRIVER_CONSOLE_GotoXY(int x,int y);

//! 输出一个字符，并将光标后移。有可能会卷屏
//! \param ch 待输出的字符
void DRIVER_CONSOLE_PutChar(char ch);

//! 输出一个某种颜色的字符
//! \param ch 待输出的字符
//! \param color 输出字符的颜色
void DRIVER_CONSOLE_PutCharWithColor(char ch, uint8_t color);

//! 输出一段字符串
//! \param str 以\0结尾的字符串
void DRIVER_CONSOLE_PutString(const char* str);

//! 输出一段某种颜色的字符串
//! \param str 以\0结尾的字符串
//! \param color 颜色
void DRIVER_CONSOLE_PutStringWithColor(const char* str, uint16_t color);

//! 设置默认的颜色
//! \param 颜色
void DRIVER_CONSOLE_SetColor(uint8_t color);

//! 返回默认的颜色
//! \return 颜色
uint16_t DRIVER_CONSOLE_GetColor();

//! 设置某一位置的字符
//! \param ch 字符
//! \param x 横坐标
//! \param y 纵坐标
void DRIVER_CONSOLE_SetChar(char ch,int16_t x, int16_t y);

//! 设置某一位置的字符,及其颜色
//! \param ch 字符
//! \param x 横坐标
//! \param y 纵坐标
//! \param color 颜色
void DRIVER_CONSOLE_SetCharWithColor(char ch, int16_t x,int16_t y, int8_t color);

#endif
