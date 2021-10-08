#ifndef OANDA__TAO_BOT_log_performance
#define OANDA__TAO_BOT_log_performance

/*
 * Oanda::TaoBot
 * closed_positions_stats_t
 * fmt
 * order_win_result_t
 * position_t
 */
#include "tao_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include <iostream>                         // std::cout, std::endl
#include <map>                              // std::map
#include <stdio.h>                          // printf, puts

void Oanda::TaoBot::log_performance() {
  closed_positions_stats_t stats = build_closed_positions_stats();
  std::map<order_win_result_t, int> closed_positions_results = stats.results;

  int win_count = closed_positions_results[order_win_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  void (*print_counts)(std::map<int, int> &
                       counts) = [](std::map<int, int> &counts) -> void {
    std::map<int, int>::iterator it;

    printf("Counts: {");

    for (it = counts.begin(); it != counts.end(); it++) {
      if (it != counts.begin()) {
        printf(", ");
      }

      printf("%d: %d", it->first, it->second);
    }

    printf("}");
  };

  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  puts("📕 Closed Positions");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;
  printf("Wins: %d (%.2f%%) • Losses: %d • Total: %d\n", win_count,
         win_percentage, closed_positions_results[order_win_result_t::LOSS],
         total_count);

  printf("Loss Streak => Current: %d • Longest: %d • ",
         stats.loss_streaks.current, stats.loss_streaks.longest);
  print_counts(stats.loss_streaks.counts);
  puts("");

  printf("Win  Streak => Current: %d • Longest: %d • ",
         stats.win_streaks.current, stats.win_streaks.longest);
  print_counts(stats.win_streaks.counts);
  puts("\n");

  printf("Current Balance: %+'.5f • Max Balance: %+'.5f • Deficit: %+'.5f\n\n",
         stats.current_balance, stats.max_balance,
         stats.current_balance - stats.max_balance);

  printf("Profits: [");

  for (int i = 0, l = this->closed_positions.size(); i < l; i++) {
    const position_t position = this->closed_positions[i];

    if (i != 0) {
      printf(", ");
    }

    printf("%+.5f:%d", position.close_order.profit,
           position.close_order.quantity);
  }

  puts("]");

  std::cout << fmt.reset << std::endl;
}

#endif
