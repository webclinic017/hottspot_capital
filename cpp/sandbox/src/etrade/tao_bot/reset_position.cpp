#ifndef ETRADE__TAO_BOT_reset_position
#define ETRADE__TAO_BOT_reset_position

/*
 * ETrade::TaoBot
 * order_status_t
 * position_t
 */
#include "tao_bot.h"

#include "build_performance.cpp"   // build_performance
#include "cut_losses.cpp"          // cut_losses
#include "set_trade_direction.cpp" // set_trade_direction
#include "write_performance.cpp"   // write_performance
#include <ctime>                   // std::time, std::time_t

void ETrade::TaoBot::reset_position() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  if (this->open_order.status != order_status_t::ORDER_EXECUTED ||
      this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  std::time_t now = std::time(nullptr);

  position_t position = {
      .close_order = this->close_order,
      .close_timestamp = (int)now,
      .open_order = this->open_order,
  };

  this->close_order_ptr = nullptr;
  this->closed_positions.push_back(position);
  this->exit_prices = exit_prices_t();
  this->open_order_ptr = nullptr;

  this->performance = build_performance();
  cut_losses();
  write_performance();
  set_trade_direction();
}

#endif
