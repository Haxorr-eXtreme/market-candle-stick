#ifndef PROJECT__CANDLESTICK_H_
#define PROJECT__CANDLESTICK_H_

#include "OrderBookEntry.h"
#include <string>
#include <vector>

class CandleStick {
 public:
  CandleStick() {}

  CandleStick(const std::string &timestamp, const std::string &product, OrderBookType orderType) : timestamp(
      timestamp), product(product), orderType(orderType) {
    open = 0.0;
    close = 0.0;
    high = 0.0;
    low = 0.0;
  }



  double getOpen() const {
    return open;
  }

  void setOpen(double open) {
    CandleStick::open = open;
  }

  double getClose() const {
    return close;
  }

  void setClose(double close) {
    CandleStick::close = close;
  }

  double getLow() const {
    return low;
  }

  void setLow(double low) {
    CandleStick::low = low;
  }

  double getHigh() const {
    return high;
  }

  void setHigh(double high) {
    CandleStick::high = high;
  }

  const std::string &getTimestamp() const {
    return timestamp;
  }

  void setTimestamp(const std::string &timestamp) {
    CandleStick::timestamp = timestamp;
  }

  const std::string &getProduct() const {
    return product;
  }

  OrderBookType getOrderType() const {
    return orderType;
  }


 private:

  double open;
  double close;
  double low;
  double high;
  std::string timestamp;
  std::string product;
  OrderBookType orderType;
};


#endif //PROJECT__CANDLESTICK_H_
