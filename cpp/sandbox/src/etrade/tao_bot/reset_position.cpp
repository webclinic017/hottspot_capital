#ifndef ETRADE__TAO_BOT_reset_position
#define ETRADE__TAO_BOT_reset_position

/*
 * ETrade::TaoBot
 * order_status_t
 * order_win_result_t
 */
#include "tao_bot.h"

#include "order_win_result.cpp"       // order_win_result
#include "write_closed_positions.cpp" // write_closed_positions
#include <time.h>                     // time, time_t

void ETrade::TaoBot::reset_position() {
  if (!this->open_order_ptr || !this->close_order_ptr) {
    return;
  }

  if (this->open_order.status != order_status_t::ORDER_EXECUTED ||
      this->close_order.status != order_status_t::ORDER_EXECUTED) {
    return;
  }

  time_t now;
  time(&now);

  position_t position = {
      .close_order = this->close_order,
      .close_timestamp = (int)now,
      .open_order = this->open_order,
  };

  this->closed_positions.push_back(position);
  write_closed_positions();
  this->close_order_ptr = nullptr;
  this->open_order_ptr = nullptr;
}

#endif
