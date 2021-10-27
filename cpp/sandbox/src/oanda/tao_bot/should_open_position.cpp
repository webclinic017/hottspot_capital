#ifndef OANDA__TAO_BOT_should_open_position
#define OANDA__TAO_BOT_should_open_position

#include "candlesticks_in_direction.cpp" // candlesticks_in_direction
#include "current_spread.cpp"            // current_spread
#include "tao_bot.h"                     // Oanda::TaoBot, fmt, order_action_t
#include <iostream>                      // std::cout, std::flush
#include <stdio.h>                       // puts

bool Oanda::TaoBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  if (!this->average_tick_price_delta) {
    return false;
  }

  if (current_spread() > 1.6e-4) {
    return false;
  }

  if (should_open_position(order_action_t::BUY)) {
    this->is_long_position = false;

    return true;
  }

  if (should_open_position(order_action_t::SELL)) {
    this->is_long_position = true;

    return true;
  }

  return false;
}

bool Oanda::TaoBot::should_open_position(order_action_t order_action) {
  if (candlesticks_in_direction(order_action)) {
    return true;
  }

  return false;
}

#endif
