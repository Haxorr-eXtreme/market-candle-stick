#ifndef PROJECT__MERKELMAIN_H_
#define PROJECT__MERKELMAIN_H_


#include <iostream>
#include <iomanip>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "CandleStick.h"


class MerkelMain {
 public:
  MerkelMain();

  /** Call this to start the sim */
  void init();

  void calculateCandlesticks();

  void plotCandlestick(const std::vector<double> &open,
                       const std::vector<double> &high,
                       const std::vector<double> &low,
                       const std::vector<double> &close,
                       const std::vector<std::string> &timeLabels);

 private:
  // utility functions
  void printMenu();

  void printHelp();

  void printMarketStats();

  void enterAsk();

  void enterBid();

  void printWallet();

  void gotoNextTimeframe();

  int getUserOption();

  void processUserOption(int userOption);

  void calculateCandlesticks(OrderBookType orderBookType);
  double calculateMeanPrice(std::vector<OrderBookEntry> &orders);
  void printCandlesticksValues();
  void printCandlesticksGraph();
  void printCandlesticksGraph(OrderBookType orderBookType);

  std::string currentTime;
  OrderBook orderBook{"D:\\PROJECT OOP CANDLESTICK\\PROJECT\\20200317.csv"};

  std::vector<CandleStick> candleSticks;
  Wallet wallet;
  const int MAX_CANDLESTICKS = 5;
  const int HEIGHT = 10;

  const int WIDTH = 8;

};


#endif //PROJECT__MERKELMAIN_H_
