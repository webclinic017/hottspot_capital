#ifndef OANDA__CLIENT
#define OANDA__CLIENT

#include "client.h" // Oanda::Client
#include "cancel_order.cpp"
#include "fetch_account.cpp"
#include "fetch_order.cpp"
#include "fetch_quote.cpp"
#include "fetch_trade.cpp"
#include "load_config.cpp" // load_config
#include "parse_quote.cpp"
#include "place_order.cpp"

Oanda::Client::Client() { load_config(); }

#endif
