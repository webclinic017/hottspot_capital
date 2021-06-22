#ifndef ETRADE__STOCK_BOT_set_moving_price_range
#define ETRADE__STOCK_BOT_set_moving_price_range

#include "compute_min_profit_price_range_ratio.cpp" // compute_min_profit_price_range_ratio
#include "stock_bot.h"                              // ETrade::StockBot, quote_t
#include <algorithm>                                // std::max, std::min
#include <vector>                                   // std::vector

void ETrade::StockBot::set_moving_price_range(const int period_seconds) {
  double high = -INFINITY;
  double low = INFINITY;
  double max_loss = INFINITY;
  double min_profit = INFINITY;
  int period;

  std::vector<quote_t>::reverse_iterator it = this->quotes.rbegin();
  const quote_t current_quote = this->quotes.back();

  while (it != this->quotes.rend() &&
         current_quote.timestamp - it->timestamp <= period_seconds) {
    high = std::max(high, it->current_price);
    low = std::min(low, it->current_price);
    period = current_quote.timestamp - it->timestamp;
    it++;
  }

  const double MOVING_DAY_RANGE_MAX_LOSS_RATIO = 0.5;
  const double max_loss_percentage = 0.005 * this->open_order.execution_price;
  const double min_profit_percentage = 0.001 * this->open_order.execution_price;
  const double price_range = high - low;

  const double buy_sell_ratio = this->is_long_position
                                    ? this->long_average_buy_sell_ratio
                                    : this->long_average_sell_buy_ratio;

  const double min_profit_price_range =
      compute_min_profit_price_range_ratio(buy_sell_ratio) * price_range;

  const double max_loss_price_range =
      MOVING_DAY_RANGE_MAX_LOSS_RATIO * price_range;

  if (this->open_order.execution_price) {
    max_loss =
        this->moving_price_range.max_loss
            ? std::min(this->moving_price_range.max_loss, max_loss_price_range)
            : max_loss_price_range;

    min_profit = this->moving_price_range.min_profit
                     ? std::min(this->moving_price_range.min_profit,
                                min_profit_price_range)
                     : min_profit_price_range;
  }

  this->moving_price_range = {
      .high = high,
      .low = low,
      .max_loss = max_loss,
      .min_profit = min_profit,
      .period = period,
  };
}

#endif