#if !defined ETRADE__SPEEDOMETER_simple_moving_average
#define ETRADE__SPEEDOMETER_simple_moving_average

#include "speedometer.h" // ETrade::Speedometer, quote_t, quotes_ptr
#include <utility>       // std::pair
#include <vector>        // std::vector

std::pair<int, double>
ETrade::Speedometer::simple_moving_average(const int ticks) {
  std::vector<quote_t> quotes = *quotes_ptr;

  if (quotes.size() < ticks) {
    return std::pair<int, double>(0, 0);
  }

  double sum = 0;
  std::vector<quote_t>::reverse_iterator it = quotes.rbegin();

  for (int i = 0; i < ticks; i++) {
    const double tick_price = it->current_price;
    sum += tick_price;
    it++;
  }

  const double average = sum / ticks;

  const quote_t current_quote = quotes.back();
  const quote_t past_quote = quotes.at(quotes.size() - ticks);

  const double current_timestamp = current_quote.timestamp;
  const double past_timestamp = past_quote.timestamp;
  const int time_delta = current_timestamp - past_timestamp;

  return std::pair<int, double>(time_delta, average);
}

#endif
