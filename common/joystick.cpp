#include "sst.hpp"

using namespace sst::registers;

namespace sst {
namespace joystick {

uint8_t get_status() {
  return sst::driver::read_register(REG_IO_PORT_A) & 0x3f;
}

};
}; // namespace sst
