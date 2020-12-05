#if !defined TD_AMERITRADE__CLIENT_get_quote
#define TD_AMERITRADE__CLIENT_get_quote

#include "client.h"               // TdAmeritrade::Client, tokens
#include "lib/curl_client.cpp"    // CurlClient
#include "lib/formatted.cpp"      // Formatted::error_message
#include "load_tokens.cpp"        // load_tokens
#include "td_ameritrade/deps.cpp" // json
#include <iostream>               // std::cout, std::endl
#include <stdexcept>              // std::invalid_argument
#include <string>                 // std::string

std::string TdAmeritrade::Client::get_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        Formatted::error_message("Please provide a stock symbol");

    throw std::invalid_argument(error_message);
  }

  return get_quote(std::string(symbol));
}

std::string TdAmeritrade::Client::get_quote(std::string symbol) {
  load_tokens();

  CurlClient::props_t props = {
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"Authorization", "Bearer " + tokens.access_token},
              {"Content-Type", "application/json"},
          },
      .method = CurlClient::http_method_t::GET,
      .query_params =
          {
              {"frequency", "1"},
              {"frequencyType", "daily"},
              {"period", "1"},
              {"periodType", "month"},
          },
      .url = "https://api.tdameritrade.com/v1/marketdata/" + symbol + "/quotes",
  };

  CurlClient curl_client(props);
  curl_client.request();

  json response = json::parse(curl_client.response.body);

  if (response.contains(symbol)) {
    return curl_client.response.body;
  }

  std::string error_message = Formatted::error_message(
      "There was a problem fetching " + symbol + "'s quote");

  std::cout << error_message
            << "here's the response: " << curl_client.response.body
            << std::endl;

  exit(1);
}

#endif
