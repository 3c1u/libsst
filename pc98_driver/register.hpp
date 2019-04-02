/**
 * @file       register.hpp
 *
 * @copyright  Copyright (c) 2019
 */

#ifndef __SST_98DRV_REGISTER_HPP
#define __SST_98DRV_REGISTER_HPP

#include "i86.h"
#include "types.h"

namespace sst {

// レジスタ制御（インライン命令）
namespace driver {

inline static void write_register(uint8_t reg, uint8_t value, bool a1 = false) {
  const uint16_t IO_ADDR_SOUND_VALUE    = 0x018A;
  const uint16_t IO_ADDR_SOUND_REGISTER = 0x0188;

  // レジスタ番地を書き込む
  i86_write_byte(IO_ADDR_SOUND_REGISTER, reg);

  // レジスタのビジーが解けるまでウェイトする
  uint8_t reg_status;
  while ((reg_status = i86_read_byte(IO_ADDR_SOUND_REGISTER)) & 0x80) {
    i86_write_byte(0x005F, 0x00);
  }

  // レジスタに書き込む値を書き込む
  i86_write_byte(IO_ADDR_SOUND_VALUE, value);
}

inline static uint8_t read_status() {
  const uint16_t IO_ADDR_STATUS_FLAG = 0x018A;
  return i86_read_byte(IO_ADDR_STATUS_FLAG);
}

inline static void write_status(uint8_t status_flag) {
  const uint16_t IO_ADDR_STATUS_FLAG = 0x018A;
  i86_write_byte(IO_ADDR_STATUS_FLAG, status_flag);
}

}; // namespace driver

}; // namespace sst

#endif
