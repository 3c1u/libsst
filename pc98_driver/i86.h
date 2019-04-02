#ifndef _I86_H
#define _I86_H

#include "types.h"

// I/Oポート入出力用関数
// Watcomコンパイラではインラインアセンブリが展開されるようになってます。
// おそらくinp, outpよりはやい（しらない）

#ifdef __WATCOMC__

#include <i86.h>
#define make_far(segment, offset) MK_FP(segment, offset)

union far_pointer_t {
  void far *_ptr;
  struct {
    uint16_t offset;
    uint16_t segment;
  } _ref;
};

/**
 * @brief        Inel 80x86
 * CPUにてportで指定されたI/Oポートにバイト値valueを出力します
 *
 * @param port   ポート番号
 * @param value  バイト値
 */
void i86_write_byte(uint16_t port, uint8_t value);

#pragma aux i86_write_byte = "out dx, al" parm[dx][al];


/**
 * @brief        Inel 80x86
 * CPUにてportで指定されたI/Oポートにワード値valueを出力します
 *
 * @param port   ポート番号
 * @param value  バイト値
 */
void i86_write_word(uint16_t port, uint16_t value);
#pragma aux i86_write_word = "out dx, ax" parm[dx][ax];

/**
 * @brief        Intel 80x86
 * CPUにてportで指定されたI/Oポートからバイト値を取得します。
 *
 * @param port   ポート番号
 */
uint8_t i86_read_byte(uint16_t port);
#pragma aux i86_read_byte = "in al, dx" value[al] parm[dx];

/**
 * @brief        Intel 80x86
 * CPUにてportで指定されたI/Oポートからワード値を取得します。
 *
 * @param port   ポート番号
 */
uint16_t i86_read_word(uint16_t port);
#pragma aux i86_read_word = "in ax, dx" value[ax] parm[dx];

#else

#define far
#define near
#define huge
#define __interrupt
#define make_far(s, o) ((void*) ((s << 4) | o))

static inline void i86_write_byte(uint16_t addr, uint8_t byte) {
    asm volatile (
        "outb %0, %1"
        : /* no output */
        : "a"(byte), "d"(addr)
        :
    );
}

static inline void i86_write_word(uint16_t addr, uint16_t word) {
    asm volatile (
        "outw %0, %1"
        : /* no output */
        : "a"(word), "d"(addr)
        :
    );
}

static inline uint8_t i86_read_byte(uint16_t addr) {
    uint8_t res = 0;
    asm volatile (
        "inb %1, %0"
        : "=a"(res)
        : "d"(addr)
        :
    );

    return res;
}

static inline uint16_t i86_read_word(uint16_t addr) {
    uint16_t res = 0;
    asm volatile (
        "inb %1, %0"
        : "=a"(res)
        : "d"(addr)
        :
    );

    return res;
}

#endif // __WATCOMC__

#endif
