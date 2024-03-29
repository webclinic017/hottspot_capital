#ifndef ETRADE__CLIENT_parse_quote
#define ETRADE__CLIENT_parse_quote

#include "client.h"           // ETrade::Client, quote_t
#include "etrade/deps.cpp"    // json
#include "lib/utils/json.cpp" // ::utils::json
#include <string>             // std::string
#include <time.h>             // time, time_t

ETrade::Client::quote_t
ETrade::Client::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = ::utils::json::parse_with_catch(response_body,
                                               "ETRADE__CLIENT_parse_quote");
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  quote_t quote;
  quote.price = full_quote["All"]["lastTrade"];
  quote.timestamp = now;

  return quote;
}

#endif
