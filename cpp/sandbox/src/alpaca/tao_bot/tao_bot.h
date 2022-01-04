#ifndef ALPACA__TAO_BOT_H
#define ALPACA__TAO_BOT_H

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "alpaca/types.cpp"         // Alpaca::t
#include "lib/formatted.cpp"        // Formatted
#include "types.cpp"                // Global::t
#include <list>                     // std::list
#include <vector>                   // std::vector

namespace Alpaca {
class TaoBot {
public:
  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using account_balance_t = Global::t::account_balance_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using order_t = Alpaca::t::order_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Global::t::performance_t;
  using position_t = Alpaca::t::position_t;
  using quote_t = Alpaca::t::quote_t;

  const double MIN_TARGET_TICK_MOVEMENT = 20.0;
  const double POSITION_TARGET_PROFIT_RATIO = 1.0e-6;

  Alpaca::Client api_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  account_balance_t account_balance;
  account_balance_t original_account_balance;
  bool is_long_position;
  char *symbol;
  double average_tick_price_delta = 0.00;
  exit_prices_t exit_prices;
  order_t *open_order_ptr = nullptr;
  order_t open_order;
  performance_t performance;
  std::map<std::string, std::string> flags;
  std::vector<position_t> closed_positions;
  std::vector<quote_t> quotes;

  account_balance_t fetch_account_balance();

  double base_quantity();
  double compute_quantity();
  double current_price();
  double loss_to_recover();
  double max_affordable_quantity();
  double position_target_movement();
  double secured_profit_ratio();

  exit_prices_t build_exit_prices();
  order_win_result_t order_win_result(const order_t *);
  performance_t build_performance();

  void fetch_quote();
  void load_performance();
  void log_start_message();
  void initialize(char *, std::map<std::string, std::string> &);
};
} // namespace Alpaca

#endif