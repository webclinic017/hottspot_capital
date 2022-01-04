#ifndef ALPACA__types
#define ALPACA__types

#include <string> // std::string

namespace Alpaca {
namespace t {
enum order_action_t {
  BUY,
  SELL,
};

enum order_status_t {
  ORDER_CANCELLED,
  ORDER_FILLED,
  ORDER_INIT,
  ORDER_PENDING,
  ORDER_TRIGGERED,
};

enum order_time_in_force_t {
  DAY,
};

enum order_type_t {
  MARKET,
};

struct order_t {
  order_action_t action;
  double execution_price = 0.00;
  std::string id = "";
  double max_profit = 0.00;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_INIT;
  const char *symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  int timestamp = 0;
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  int close_timestamp = 0;
  order_t open_order;
};

struct quote_t {
  double price;
  long int timestamp;
};
} // namespace t
} // namespace Alpaca
#endif