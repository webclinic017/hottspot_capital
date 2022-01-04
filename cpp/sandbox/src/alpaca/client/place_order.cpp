#ifndef ALPACA__CLIENT_place_order
#define ALPACA__CLIENT_place_order

/*
 * Alpaca::Client
 * order_action_t
 * order_status_t
 * order_t
 */
#include "client.h"

#include "alpaca/constants.cpp"            // Alpaca::constants
#include "deps.cpp"                        // json, _json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/float.cpp"             // ::utils::float_
#include "lib/utils/json.cpp"              // ::utils::json
#include "post.cpp"                        // post
#include <ctime>                           // std::time, std::time_t
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::stod

CurlClient Alpaca::Client::place_order(order_t *order) {
  std::string url = this->config.base_url + "/v2/orders";

  json body = R"(
    {
      "qty": 1.0000,
      "side": "BUY|SELL",
      "symbol": "XXXX",
      "time_in_force": "day",
      "type": "MARKET"
    }
  )"_json;

  body["order"]["qty"] = order->quantity;
  body["order"]["side"] = Alpaca::constants::ORDER_ACTIONS[order->action];
  body["order"]["symbol"] = order->symbol;
  body["order"]["time_in_force"] =
      Alpaca::constants::ORDER_TIMES_IN_FORCE[order->time_in_force];
  body["order"]["type"] = Alpaca::constants::ORDER_TYPES[order->type];

  CurlClient curl_client = post({
      .body = body.dump(),
      .method = CurlClient::http_method_t::POST,
      .url = url,
  });

  std::time_t now = std::time(nullptr);

  json response = ::utils::json::parse_with_catch(curl_client.response.body,
                                                  "ALPACA__CLIENT_place_order");

  std::cout << fmt.yellow << fmt.bold;
  printf("Order payload: %s\n", body.dump(2).c_str());
  std::cout << fmt.reset;

  std::cout << fmt.yellow << fmt.bold;
  printf("Order response: %s\n", response.dump(2).c_str());
  std::cout << fmt.reset;

  order->id = response["id"];
  order->status = order_status_t::ORDER_PENDING;
  order->timestamp = now;

  return curl_client;
}

#endif