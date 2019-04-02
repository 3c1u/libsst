#include "console.hpp"
#include "types.h"

namespace console {

void print_char(char c) {
  _asm {
    push ax
    mov dl, c
    mov ah, 0x02
    int 0x21
    pop ax
  };
}

void print_string(const char *str) {
  while (*str) {
    print_char(*str);
    str++;
  }
}

void print_hex_4(uint8_t value) {
  if (value < 10)
    print_char(value + '0');
  else
    print_char(value + 'A' - 0x0A);
}

void print_hex_8(uint8_t value) {
  print_hex_4(value >> 4);
  print_hex_4(value & 0x0F);
}

void print_hex_16(uint16_t value) {
  print_hex_8(value >> 8);
  print_hex_8(value & 0xFF);
}

void print_hex_32(uint32_t value) {
  print_hex_16(value >> 16);
  print_hex_16(value & 0xFFFF);
}

};
