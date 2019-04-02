#ifndef __SST_98DRV_TIMER_HOOK_HPP
#define __SST_98DRV_TIMER_HOOK_HPP

#include "i86.h"

namespace sst {
namespace driver {
void hook_timer_handler(void far (*timer_handler)());
void unhook_timer_handler();
};
}; // namespace sst

#endif