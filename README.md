# Market Candle Stick Trading Simulator

A C++ application that simulates cryptocurrency trading with real-time candlestick chart visualization. This project demonstrates order book management, wallet functionality, and ASCII-based candlestick chart plotting.

## Features

- **Order Book Management**: Handles bid/ask orders with CSV data import
- **Trading Simulation**: Interactive trading with wallet balance tracking
- **Candlestick Charts**: ASCII-based visualization of price movements
- **Real-time Data Processing**: Processes historical trading data from CSV files
- **Interactive Menu System**: User-friendly command-line interface

## Project Structure

```
├── main.cpp                 # Entry point with sample data
├── MerkelMain.cpp/.h        # Main application logic and menu system
├── OrderBook.cpp/.h         # Order book management and matching
├── OrderBookEntry.cpp/.h    # Individual order representation
├── CandleStick.cpp/.h       # Candlestick data structure
├── Wallet.cpp/.h            # Wallet and currency management
├── CSVReader.cpp/.h         # CSV data parsing utilities
└── 20200317.csv            # Sample trading data (ETH/BTC)
```

## Core Components

### OrderBook
- Manages buy/sell orders
- Matches asks to bids
- Provides price statistics (high, low, mean)
- Handles time-based order processing

### CandleStick
- Represents OHLC (Open, High, Low, Close) data
- Tracks price movements over time
- Supports both bid and ask candlesticks

### Wallet
- Multi-currency balance tracking
- Order fulfillment validation
- Automatic balance updates on trades

### CSVReader
- Parses trading data from CSV files
- Converts string data to OrderBookEntry objects
- Handles tokenization and data validation

## Getting Started

### Prerequisites
- C++ compiler with C++11 support or later
- Standard C++ libraries

### Compilation
```bash
g++ -std=c++11 -o trading_simulator *.cpp
```

### Running the Application
```bash
./trading_simulator
```

## Usage

The application provides an interactive menu with the following options:

1. **Print help** - Display trading instructions
2. **Print exchange stats** - Show market statistics
3. **Make an offer** - Place a sell order
4. **Make a bid** - Place a buy order
5. **Print wallet** - Display current balances
6. **Continue** - Advance to next time frame
7. **Calculate Candle Sticks** - Generate candlestick data
8. **Print Candle Stick Values** - Display OHLC data
9. **Print Candle Stick Graph** - Show ASCII candlestick charts

### Sample Trading
When placing orders, use the format:
```
product,price,amount
```
Example: `ETH/BTC,200,0.5`

## Data Format

The CSV file should contain trading data in the format:
```
timestamp,product,orderType,price,amount
2020/03/17 17:01:24.884492,ETH/BTC,bid,0.02187308,7.44564869
```

## Candlestick Visualization

The application generates ASCII-based candlestick charts showing:
- **Open/Close prices** (represented by '0')
- **High/Low wicks** (represented by '|')
- **Price range** (represented by '-')
- **Time labels** for each candlestick

## Key Features

- **Real-time Processing**: Processes historical data in chronological order
- **Order Matching**: Automatically matches compatible buy/sell orders
- **Balance Validation**: Ensures sufficient funds before order placement
- **Multi-product Support**: Handles different cryptocurrency pairs
- **Time-based Simulation**: Advances through trading periods

## Technical Details

- **Language**: C++11
- **Data Structures**: Vectors, Maps, Enums
- **File I/O**: CSV parsing and processing
- **Memory Management**: RAII principles
- **Error Handling**: Exception handling for invalid inputs

## Sample Output

The application displays candlestick charts in ASCII format:
```
 0.90 |     |     |     |     |
 0.80 |  |--|  |--|  |--|  |--|
 0.70 |  |00|  |00|  |00|  |00|
 0.60 |  |--|  |--|  |--|  |--|
 0.50 |     |     |     |     |
      4:00  12:00 16:00 06:00 11:00
```

## Contributing

This project serves as an educational example of:
- Object-oriented programming in C++
- Financial data processing
- ASCII art visualization
- Trading system simulation

## License

This project is for educational purposes. Feel free to use and modify for learning purposes.
