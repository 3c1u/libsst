#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "types.h"

namespace console {

void print_char  (char c);
void print_string(const char *str);

void print_hex_4(uint8_t value);
void print_hex_8(uint8_t value);
void print_hex_16(uint16_t value);
void print_hex_32(uint32_t value);

#define _DEBUG
#ifdef _DEBUG
#define debug_string(msg) print_string(msg)
#else
#define debug_string()
#endif

};

#endif
