#ifndef OANDA__TAO_BOT_base_quantity
#define OANDA__TAO_BOT_base_quantity

#include "tao_bot.h" // Oanda::TaoBot
#include <math.h>    // pow

double Oanda::TaoBot::base_quantity() {
  const double max_buying_potential =
      this->account_balance.balance * this->account_balance.margin_multiplier;

  const double dollars_per_unit = convert_price(1.0, base_currency(), "USD");

  const double max_affordable_quantity_ =
      max_buying_potential / dollars_per_unit;

  return max_affordable_quantity_ / pow(2, this->MAX_EXPECTED_LOSS_STREAK + 1);
}

#endif
