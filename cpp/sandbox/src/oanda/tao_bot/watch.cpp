#ifndef OANDA__TAO_BOT_watch
#define OANDA__TAO_BOT_watch

#include "await_market_open.cpp"         // await_market_open
#include "build_candlesticks.cpp"        // build_candlesticks
#include "clear_stale_open_order.cpp"    // clear_stale_open_order
#include "close_position.cpp"            // close_position
#include "fetch_quote.cpp"               // fetch_quote
#include "is_market_open.cpp"            // is_market_open
#include "log_account_balance.cpp"       // log_account_balance
#include "log_candlesticks.cpp"          // log_candlesticks
#include "log_end_of_trading_period.cpp" // log_end_of_trading_period
#include "log_performance.cpp"           // log_performance
#include "log_position.cpp"              // log_position
#include "log_position_results.cpp"      // log_position_results
#include "log_quote.cpp"                 // log_quote
#include "open_position.cpp"             // open_position
#include "reset_position.cpp"            // reset_position
#include "set_close_position_prices.cpp" // set_open_position_prices
#include "set_open_position_prices.cpp"  // set_open_position_prices
#include "set_position_status.cpp"       // set_order_statuses
#include "should_terminate.cpp"          // should_terminate
#include "tao_bot.h"                     // Oanda::TaoBot
#include <iostream>                      // std::cout, std::flush
#include <unistd.h>                      // usleep

void Oanda::TaoBot::watch() {
  while (!is_market_open()) {
    await_market_open();
  }

  while (!should_terminate()) {
    fetch_quote();
    build_candlesticks();

    log_account_balance();
    log_quote();
    log_candlesticks();
    log_position();
    log_performance();

    set_position_status();

    clear_stale_open_order();
    open_position();
    set_open_position_prices();

    close_position();
    set_close_position_prices();

    log_position_results();
    reset_position();

    usleep(1e6);
  }

  log_end_of_trading_period();
}

#endif
