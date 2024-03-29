#ifndef ETRADE__TAO_BOT_trim_old_quotes
#define ETRADE__TAO_BOT_trim_old_quotes

#include "build_performance.cpp" // build_performance
#include "tao_bot.h"             // ETrade::TaoBot, quote_t
#include <time.h>                // time_t, time
#include <vector>                // vector

void ETrade::TaoBot::trim_old_quotes() {
  const performance_t stats = this->performance;

  if (stats.loss_streaks.current) {
    return;
  }

  const int max_time_limit = 5 * 60;
  int i = 0;
  std::vector<quote_t>::iterator it = this->quotes.begin();
  time_t now;

  time(&now);

  while ((now - it->timestamp) > max_time_limit) {
    it++;
    i++;
  }

  if (!i) {
    return;
  }

  this->quotes.erase(this->quotes.begin(), this->quotes.begin() + i);
}

#endif
