#include <assert.h>
#include "psg.hpp"

using namespace sst::registers;

namespace sst {
namespace psg {

enum {
  CHANNEL_INVALID = 0xFF,
};

class PSGChannel : public ISSTChannel {
public:
  PSGChannel(uint8_t channel = CHANNEL_INVALID)
      : _channel(channel), _pitch(0x00), _portamento_rate(0x00), _n_cur(0x00) {
    // ステータスのリセット
    _status._ = 0x00;

    // チップのリセット
    reset();
  }

  ~PSGChannel() {}

  // ISSTChannelの実装
  void key_on(uint8_t key_number, uint8_t velocity) override {
    // チャンネル値が不正でないことをチェック
    assert(_channel != CHANNEL_INVALID);

    // ノートナンバーの退避を行う
    _n_cur  = key_number;

    // キーオンフラグをオンにする
    _status.flags.key_on = true;
  }

  void key_off(uint8_t key_number) override {
    // キーオンフラグをオフにする
    _status.flags.key_on = false;
  }

  void on_tick() override {
    // 毎ティックの処理

    // ソフトウェアエンベロープ
    if (_status.flags.software_envelope) {

    }

    // ポルタメントの更新
  }

private:
  uint8_t _channel;
  union {
    uint8_t _;
    struct {
      bool key_on : 1;
      bool portamento : 1;
      bool legato : 1;
      bool software_envelope : 1;
      bool hardware_envelope : 1;
      bool reserved : 3;
    } flags;
  } _status;

  uint8_t _n_cur;

  uint8_t _pitch;
  uint8_t _portamento_rate;

  void reset() {
    // チップのリセット
  }
};

}; // namespace psg
}; // namespace sst
