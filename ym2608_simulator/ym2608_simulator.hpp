/**
 * @file       ym2608_simulator.hpp
 * @copyright  Copyright (c) 2019
 */

#ifndef __YM2608_SIMUALTOR_HPP
#define __YM2608_SIMUALTOR_HPP

#include <stdlib.h>
#include <stdint.h>

namespace sst::driver {

// simulator-specific functions
void    init_simulator(uint32_t sampling_freq);
void    reset();
void    process_buffer(size_t buffer_size, float *buffer);


void    write_register(uint8_t reg, uint8_t value, bool a1 = false);
uint8_t read_status();
void    write_status(uint8_t status_flag);
void    hook_timer_handler(void (*timer_handler)());
void    unhook_timer_handler();

}; // namespace sst::driver

#endif
