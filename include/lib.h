#ifndef __LIB_H__
#define __LIB_H__

#include<stdarg.h>
#include<stddef.h>
#include"uart.h"

extern void lib_delay(volatile int count);
extern int lib_vsnprintf(char * out, size_t n, const char* s, va_list vl);
extern int lib_vprintf(const char* s, va_list vl);
extern int lib_printf(const char* s, ...);
#endif // !__LIB_H__
