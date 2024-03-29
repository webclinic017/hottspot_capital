#ifndef ETRADE__TAO_BOT_fetch_quote
#define ETRADE__TAO_BOT_fetch_quote

#include "tao_bot.h" // ETrade::TaoBot, quote_t
#include <string>    // std::string

void ETrade::TaoBot::fetch_quote() {
  std::string quote_string = this->api_client.fetch_quote(this->symbol);
  quote_t current_quote = this->api_client.parse_quote(quote_string);

  this->quotes.push_back(current_quote);
}

#endif
