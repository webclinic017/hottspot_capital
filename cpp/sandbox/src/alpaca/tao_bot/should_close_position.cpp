#ifndef ALPACA__TAO_BOT_should_close_position
#define ALPACA__TAO_BOT_should_close_position

/*
 * Alpaca::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "build_exit_prices.cpp"        // build_exit_prices
#include "is_end_of_trading_period.cpp" // is_end_of_trading_period
#include "max_account_loss_reached.cpp" // max_account_loss_reached
#include "position_target_movement.cpp" // position_target_movement
#include <math.h>                       // abs

bool Alpaca::TaoBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_FILLED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_INIT) {
    return false;
  }

  if (is_end_of_trading_period()) {
    return true;
  }

  if (max_account_loss_reached()) {
    return true;
  }

  this->exit_prices = build_exit_prices();

  if (this->open_order.max_profit >= this->exit_prices.min_profit &&
      this->open_order.profit >= this->exit_prices.lower_secure_profit &&
      this->open_order.profit <= this->exit_prices.upper_secure_profit) {
    return true;
  }

  if (this->open_order.profit <= exit_prices.max_loss) {
    return true;
  }

  return false;
}

#endif
