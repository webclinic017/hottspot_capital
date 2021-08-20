#ifndef ETRADE__STOCK_BOT_set_profit
#define ETRADE__STOCK_BOT_set_profit

#include "compute_profit.cpp" // compute_profit
#include "stock_bot.h"        // ETrade::StockBot, order_t
#include <algorithm>          // std::max
#include <time.h>             // time time_t

void ETrade::StockBot::set_profit(order_t *order) {
  const double profit = compute_profit(order, &(this->quotes.back()));

  if (profit >= order->max_profit || !order->max_profit_timestamp) {
    time_t now;
    time(&now);

    order->max_profit_timestamp = now;
  }

  order->max_profit = std::max(profit, order->max_profit);
  order->profit = profit;
}

void ETrade::StockBot::set_profit(order_t *close_order,
                                  const order_t *open_order) {
  close_order->profit = compute_profit(close_order, open_order);
}

#endif
