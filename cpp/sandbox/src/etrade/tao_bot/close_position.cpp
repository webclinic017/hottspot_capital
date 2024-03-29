#ifndef ETRADE__TAO_BOT_close_position
#define ETRADE__TAO_BOT_close_position

#include "etrade/constants.cpp"      // ETrade::constants
#include "should_close_position.cpp" // should_close_position
#include "tao_bot.h"                 // ETrade::TaoBot, fmt
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // printf

void ETrade::TaoBot::close_position() {
  if (!should_close_position()) {
    return;
  }

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  this->api_client.place_order(this->close_order_ptr);

  std::cout << fmt.bold << fmt.cyan << std::endl;
  printf("%s %s: Placed closing order.\n", log_icon, order_action);
  std::cout << fmt.reset;
}

#endif
