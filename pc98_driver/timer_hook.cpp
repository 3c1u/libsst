#include "timer_hook.hpp"
#include <assert.h>

typedef void __interrupt far (*fptr_t)();

static fptr_t prev_vect = nullptr;
static fptr_t handler   = nullptr;
namespace sst {
namespace driver {

static void far __interrupt __hook_timer_handler() {
  _asm("sti"); // 外部割り込みの許可

  handler(); // hook_...で指定したハンドラーの呼び出し

  // EOI (slave)
  i86_write_byte(0x08, 0x20);

  if (!i86_read_byte(0x08)) { // EOI (master)
    i86_write_byte(0x00, 0x20);
  }
}

void hook_timer_handler(void far (*timer_handler)()) {
  fptr_t far *ivect = reinterpret_cast<fptr_t far *>(0x50);
  assert(prev_vect == nullptr);

  // 外部割り込みの禁止
  _asm("cli");

  // ベクターテーブルの設定
  prev_vect = *ivect;
  *ivect    = __hook_timer_handler;

  // ハンドラーの設定
  handler = timer_handler;
  
  // PICの設定 (slave)
  i86_write_byte(0x0A, i86_read_byte(0x0A) & 0xEF);

  _asm {
    jmp .+2 // パイプラインのクリア
    sti // 割り込みの許可
  }
}

void unhook_timer_handler() {
  // 外部割り込みの禁止
  _asm("cli");

  // 割り込みハンドラーを元に戻す
  fptr_t *ivect = reinterpret_cast<fptr_t *>(0x50);
  *ivect        = prev_vect;

  // PICの設定 (slave)
  i86_write_byte(0x0A, i86_read_byte(0x0A) | (~0xEF));

  _asm {
    jmp .+2 // パイプラインのクリア
    sti // 割り込みの許可
  }

  prev_vect = nullptr;
}

}; // namespace driver
}; // namespace sst
