// YM2608のリズムセクションのドライバ

#include "sst.hpp"

using namespace sst::registers;

namespace sst {

enum _RhythmRegMapping {
  RREG_BASS_DRUM  = 0x18,
  RREG_SNARE_DRUM = 0x19,
  RREG_RIMSHOT    = 0x1D,
  RREG_HI_HAT     = 0x1B,
  RREG_TOM        = 0x1C,
  RREG_TOP_CYMBAL = 0x1A,
};

class RhythmChannel : public ISSTChannel {
public:
  RhythmChannel() {
    // リズムチャンネル
    reset_channel();
  }

  ~RhythmChannel() { reset_channel(); }

  // チャンネルのリセット
  void reset_channel() {
    // すべてのドラムをオフにする（dump）
    driver::write_register(REG_DUMP_RHYTHM_KEY_ON, 0xBF);
  }

  // ISSTChannelの実装
  void key_on(uint8_t key_number, uint8_t velocity) override {
    if (!velocity) {
      // ベロシティが0ならキーオフ
      key_off(key_number);
      return;
    }

    if (key_number < 6) {
      // OPNAのリズム音源
      driver::write_register(RREG_BASS_DRUM + key_number,
                             (velocity >> 3) | 0xC0);
      driver::write_register(REG_DUMP_RHYTHM_KEY_ON, 1 << key_number);
    } else {
      // SSTドラム音源（未実装）
    }
  }

  void key_off(uint8_t key_number) override {
    enum {
      DUMP = 0x80,
    };

    if (key_number < 6) {
      driver::write_register(REG_DUMP_RHYTHM_KEY_ON, DUMP | (1 << key_number));
    } else {
      // SSTドラム音源（未実装）
    }
  }

private:
};

} // namespace sst
