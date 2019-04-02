/**
 * @file       psg.hpp
 * @copyright  Copyright (c) 2019
 * 
 */
#ifndef __SST_PSG_HPP
#define __SST_PSG_HPP

#include "sst.hpp"

namespace sst {
namespace psg {

enum {
  CHANNEL_INVALID = 0xFF,
};

class PSGChannel : public ISSTChannel {
public:
  PSGChannel(uint8_t channel = CHANNEL_INVALID);
  ~PSGChannel();

  // ISSTChannelの実装
  void key_on (uint8_t key_number, uint8_t velocity) override;
  void key_off(uint8_t key_number) override;

private:
  uint8_t _channel;
  uint8_t _status;
  uint8_t _portamento;
};

};
};

#endif
