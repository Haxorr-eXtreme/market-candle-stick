#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);
    calculateCandlesticks();

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

double MerkelMain::calculateMeanPrice(std::vector<OrderBookEntry>& orders) {
    double totalValue = 0.0;
    double totalPrice = 0.0;
    for (OrderBookEntry& e : orders) {
        totalValue += e.amount * e.price;
        totalPrice += e.price;
    }
    if (totalPrice == 0.0) {
        return 0.0;
    }
    return totalValue / totalPrice;
}

void MerkelMain::calculateCandlesticks() {
    // Calculate the candle sticks separately for asks and bids
    calculateCandlesticks(OrderBookType::ask);
    calculateCandlesticks(OrderBookType::bid);
}

void MerkelMain::calculateCandlesticks(OrderBookType orderBookType) {
    std::string earliestTime = orderBook.getEarliestTime();
    std::string currTime = earliestTime;
    for (std::string const& p : orderBook.getKnownProducts()) {
        do {
            std::vector<OrderBookEntry> currOrders = orderBook.getOrders(orderBookType,
                p, currTime);
            if (currOrders.empty()) {
                currTime = orderBook.getNextTime(currTime);
                continue; // no order for this product/time combination so skip it
            }
            CandleStick candleStick = CandleStick(currTime, p, orderBookType);
            candleStick.setLow(OrderBook::getLowPrice(currOrders));
            candleStick.setHigh(OrderBook::getHighPrice(currOrders));
            candleStick.setClose(calculateMeanPrice(currOrders));
            if (!candleSticks.empty() && candleSticks.back().getProduct() == p &&
                candleSticks.back().getOrderType() == orderBookType) {
                candleStick.setOpen(candleSticks.back().getClose());
            }
            candleSticks.push_back(candleStick);
            currTime = orderBook.getNextTime(currTime);
            std::cout << currTime << " " << p << std::endl;
        } while (currTime != earliestTime); // all orders seen, time gets looped around
    }
}

void MerkelMain::printCandlesticksValues() {
    for (auto& candleStick : candleSticks) {
        std::cout << "Time: " << candleStick.getTimestamp() << std::endl;
        std::cout << "Product: " << candleStick.getProduct() << std::endl;
        std::cout << "Order type: " << OrderBookEntry::orderBookTypeToString(candleStick.getOrderType()) << std::endl;
        std::cout << std::setprecision(5) << "Open: " << candleStick.getOpen() << ", Close: " << candleStick.getClose() << ", High: "
            << candleStick.getHigh() << ", Low: " << candleStick.getLow() << std::endl;
        //        getchar(); // use this to print line by line
    }
}
void MerkelMain::printCandlesticksGraph() {
    printCandlesticksGraph(OrderBookType::ask);
    printCandlesticksGraph(OrderBookType::bid);
}

void MerkelMain::printCandlesticksGraph(OrderBookType orderBookType) {
    int i = 0;
    while (i < candleSticks.size()) {
        std::string currProduct = candleSticks[i].getProduct();
        std::cout << " Candle Stick Graph for: " << currProduct << " "
            << OrderBookEntry::orderBookTypeToString(orderBookType) << std::endl;

        std::vector<double> open;
        std::vector<double> high;
        std::vector<double> low;
        std::vector<double> close;
        std::vector<std::string> timeLabels;

        for (int j = 0; j < MAX_CANDLESTICKS && i < candleSticks.size(); ++j, ++i) {
            if (currProduct != candleSticks[i].getProduct()) break;

            open.push_back(candleSticks[i].getOpen());
            close.push_back(candleSticks[i].getClose());
            low.push_back(candleSticks[i].getLow());
            high.push_back(candleSticks[i].getHigh());
            timeLabels.push_back(candleSticks[i].getTimestamp());
        }

        // Modify this part to customize the output before plotting
        std::cout << "Candlestick Data:\n";
        for (int k = 0; k < open.size(); ++k) {
            std::cout << "Time: " << timeLabels[k]
                << " Open: " << open[k]
                << " High: " << high[k]
                << " Low: " << low[k]
                << " Close: " << close[k] << std::endl;
        }

        plotCandlestick(open, high, low, close, timeLabels);
    }
}



void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue
    std::cout << "6: Continue " << std::endl;
    // 7 calculate candle sticks
    std::cout << "7: Calculate Candle Sticks " << std::endl;
    // 8 Print candle stick values
    std::cout << "8: Print Candle Stick Values " << std::endl;
    // 9 Print candle stick graph
    std::cout << "9: Print Candle Stick Graph " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
            p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
              
                wallet.processSale(sale);
            }
        }

    }

    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-9" << std::endl;
    std::getline(std::cin, line);
    try {
        userOption = std::stoi(line);
    }
    catch (const std::exception& e)
    {
     
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption < 1 || userOption > 9) 
    {
        std::cout << "Invalid choice. Choose 1-9" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    if (userOption == 7)
    {
        calculateCandlesticks();
    }
    if (userOption == 8)
    {
        printCandlesticksValues();
    }
    if (userOption == 9)
    {
        printCandlesticksGraph();
    }
}

void MerkelMain::plotCandlestick(const std::vector<double>& open,
    const std::vector<double>& high,
    const std::vector<double>& low,
    const std::vector<double>& close,
    const std::vector<std::string>& timeLabels) {

    char candlestickGrid[MAX_CANDLESTICKS][HEIGHT][WIDTH];

    for (int i = 0; i < MAX_CANDLESTICKS; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            for (int k = 0; k < WIDTH; ++k) {
                candlestickGrid[i][j][k] = ' ';
            }
        }
    }

    for (size_t i = 0; i < open.size(); ++i) {
        double range = high[i] - low[i];
        double bodyRange = abs(open[i] - close[i]);
        int bodyHeight = static_cast<int>((bodyRange / range) * HEIGHT);

        for (int j = 0; j < HEIGHT; ++j) {
            for (int k = 0; k < WIDTH; ++k) {
                if (k == WIDTH / 2) {
                    candlestickGrid[i][j][k] = '|';
                }
                else if (j < (HEIGHT - bodyHeight) / 2 || j >= (HEIGHT + bodyHeight) / 2) {
                    candlestickGrid[i][j][k] = '-';
                }
                else {
                    candlestickGrid[i][j][k] = '0';
                }
            }
        }
    }

    for (int i = HEIGHT - 1; i >= 0; --i) {
        std::cout << std::setw(4) << std::setfill(' ') << std::fixed << std::setprecision(2) << i * 0.1 << " | ";
        for (size_t j = 0; j < open.size(); ++j) {
            for (int k = 0; k < WIDTH; ++k) {
                std::cout << candlestickGrid[j][i][k];
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::setw(6) << std::setfill(' ') << ' ';
    for (const std::string& label : timeLabels) {
        std::cout << std::setw(WIDTH) << label;
    }
    std::cout << std::endl;
}

