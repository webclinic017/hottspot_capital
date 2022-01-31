#ifndef OANDA__TAO_BOT_compute_quantity
#define OANDA__TAO_BOT_compute_quantity

#include "base_quantity.cpp"           // base_quantity
#include "build_exit_prices.cpp"       // build_exit_prices
#include "loss_to_recover.cpp"         // loss_to_recover
#include "max_affordable_quantity.cpp" // max_affordable_quantity
#include "tao_bot.h"                   // Oanda::TaoBot
#include <algorithm>                   // std::min
#include <math.h>                      // abs, ceil

int Oanda::TaoBot::compute_quantity() {
  const double max_affordable_quantity_ = max_affordable_quantity();

  if (!max_affordable_quantity_) {
    return 0;
  }

  const double loss_to_recover_ = abs(loss_to_recover());

  if (!loss_to_recover_) {
    return std::min(base_quantity(), max_affordable_quantity_);
  }

  exit_prices_t exit_prices_ = build_exit_prices();
  const double quantity_ = loss_to_recover_ / abs(exit_prices_.max_loss);

  return ceil(std::min(quantity_, max_affordable_quantity_));
}

#endif
