#include "Wallet.h"
#include <iostream>
#include "MerkelMain.h"

int main()
{
    std::vector<double> Low = {1.18, 1.23, 1.28, 1.26, 1.32};
    std::vector<double> Open = {1.20, 1.25, 1.30, 1.28, 1.35};
    std::vector<double> High = {2.22, 1.27, 1.34, 1.29, 1.38};
    std::vector<double> Close = {1.21, 1.26, 1.32, 1.27, 1.36};
    std::vector<std::string> timeLabels = {"4:00", "12:00", "16:00", "06:00", "11:00"};



    MerkelMain app{};

    app.plotCandlestick(Open, High, Low, Close, timeLabels);
    app.init();

}
