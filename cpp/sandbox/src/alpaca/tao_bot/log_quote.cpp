#ifndef ALPACA__TAO_BOT_log_quote
#define ALPACA__TAO_BOT_log_quote

/*
 * Alpaca::TaoBot
 * fmt
 * quote_t
 */
#include "tao_bot.h"

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // utils::float_
#include "lib/utils/integer.cpp" // utils::integer_
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf

void Alpaca::TaoBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = this->quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote =
      ticks > 1 ? &(this->quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = this->quotes.back();

  if (previous_quote) {
    if (current_quote.price > previous_quote->price) {
      log_color = fmt.green;
    } else if (current_quote.price < previous_quote->price) {
      log_color = fmt.red;
    }
  }

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Quote\n", this->symbol);

  std::cout << fmt.reset << fmt.bold << log_color;
  printf("Current: %'.2f\n", ::utils::float_::to_currency(current_quote.price));

  std::cout << fmt.reset << std::endl;
}

#endif
