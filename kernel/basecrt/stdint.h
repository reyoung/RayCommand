#ifndef BASECRT_STDINT_H
#define BASECRT_STDINT_H


//! 像标准库中的stdint一样，定义一些知道长度的类型
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int  uint32_t;
typedef unsigned long long uint64_t;

typedef char int8_t;
typedef short int16_t;
typedef int  int32_t;
typedef long long int64_t;


//! 定义bool型为int。理论上int型操作最快速。
typedef int boolean;

//! False =0, True=1, 与C++标准一致。
enum {
	False = 0,
	True = 1
};


#endif
