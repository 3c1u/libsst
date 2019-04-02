/**
 * @file       sst.hpp
 * @copyright  Copyright (c) 2019
 */

#ifndef __SST_HPP
#define __SST_HPP

#ifdef __TARGET_PC98
#include "../pc98_driver/pc98_driver.hpp"
#else
#include "../ym2608_simulator/ym2608_simulator.hpp"
#endif

namespace sst {

namespace registers {
enum {
  /* PSG音源の設定 */
  REG_CH_A_FINE_TUNE = 0x00,
  REG_CH_A_COARSE_TUNE,

  REG_CH_B_FINE_TUNE,
  REG_CH_B_COARSE_TUNE,

  REG_CH_C_FINE_TUNE,
  REG_CH_C_COARSE_TUNE,

  //--
  REG_NOISE_TUNE,
  REG_NOISE_TONE_MIXING,

  //--
  REG_CH_A_AMPLITUDE,
  REG_CH_B_AMPLITUDE,
  REG_CH_C_AMPLITUDE,

  //--
  REG_ENV_PERIOD_FINE_TUNE,
  REG_ENV_PERIOD_COARSE_TUNE,
  REG_ENV_SHAPE,

  /* Atari規格のジョイスティックの入力 */
  REG_IO_PORT_A,
  REG_IO_PORT_B,

  /* リズム機能 */
  REG_DUMP_RHYTHM_KEY_ON,                // write-only, YM2608
  REG_RHYTHM_TONAL_LEVEL,                // write-only, YM2608
  REG_LSI_TEST,                          // write-only, YM2608
  REG_OUTPUT_SELECT_INST_LEVEL_0 = 0x18, // write-only, YM2608

  /* FM音源 */
  REG_TEST          = 0x21, // write-only
  REG_LFO           = 0x22, // write-only, YM2608
  REG_TIMER_A_UPPER = 0x24, // write-only
  REG_TIMER_A_LOWER,        // write-only
  REG_TIMER_B,              // write-only
  REG_TIMER_CTRL_CH3_MODE,  // write-only

  REG_KEY_ON_OFF_CTRL,    // write-only
  REG_KEY_IRQ_ENABLE_SCH, // write-only, YM2608

  REG_SET_PRESCALER  = 0x2D, // write-only
  REG_SET_THIRD      = 0x2E, // write-only
  REG_SET_HALF_COUNT = 0x2F, // write-only

  //--
  REG_DETUNE_MULTIPLE            = 0x30, // write-only (~ 0x3E)
  REG_TOTAL_LEVEL                = 0x40, // write-only (~ 0x4E)
  REG_KEY_SCALE_ATTACK_RATE      = 0x50, // write-only (~ 0x5E)
  REG_DECAY_RATE_AMON            = 0x60, // write-only (~ 0x6E)
  REG_SUSTAIN_RATE               = 0x70, // write-only (~ 0x7E)
  REG_SUSTAIN_LEVEL_RELEASE_RATE = 0x80, // write-only (~ 0x8E)
  REG_SSG_TYPE_ENV_CTRL          = 0x90, // write-only (~ 0x90)
  REG_F_NUM_1                    = 0xA0, // write-only (~ 0xA2)
  REG_BLOCK_F_NUM_2              = 0xA4, // write-only (~ 0xA6)
  REG_3CH_F_NUM_1                = 0xA8, // write-only (~ 0xAA)
  REG_3CH_BLOCK_F_NUM_2          = 0xAC, // write-only (~ 0xAE)

  REG_SELF_FB_CONNECTION = 0xB0, // write-only (~ 0xB2)
  REG_PMS_AMS_LR         = 0xB4, // write-only (~ 0xB6, YM2608)

  //--
  REG_ID_NUM = 0xFF, // read-only (YM2608)
};
};

class ISSTChannel {
  virtual void key_on (uint8_t key_number, uint8_t velocity) {}
  virtual void key_off(uint8_t key_number) {}
};

}; // namespace sst

#endif
