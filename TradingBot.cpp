#include "TradingBot.h"
#include "Order.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Defs.h"


TradingBot::TradingBot(CapitalManager *_capitalManager, ObjectManager *_objectManager)
: capitalManager(_capitalManager), objectManager(_objectManager)
{
    takeProfit = AddTradingParameter("Take Profit", PipsToPrice(20), PipsToPrice(100), PipsToPrice(10));
    stopLosses = AddTradingParameter("Stop Losses", PipsToPrice(5), PipsToPrice(50), PipsToPrice(10));
    lots = AddTradingParameter("Lots", 0.05, 0.5, 0.1);
}

TradingBot::~TradingBot()
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        delete indicators[i];
    indicators.clear();
}

void TradingBot::Buy(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tBUY, timeIndex, lots->GetCurrentValue(), price, price + takeProfit->GetCurrentValue(), price - stopLosses->GetCurrentValue()));
    objectManager->AddObject(new OrderBar(timeIndex, price, price + takeProfit->GetCurrentValue(), price - stopLosses->GetCurrentValue()));
}

void TradingBot::Sell(double price, int timeIndex)
{
    capitalManager->AddOrder(CreateOrder(tSELL, timeIndex, lots->GetCurrentValue(), price, price - takeProfit->GetCurrentValue(), price + stopLosses->GetCurrentValue()));
    objectManager->AddObject(new OrderBar(timeIndex, price, price - takeProfit->GetCurrentValue(), price + stopLosses->GetCurrentValue()));
}

void TradingBot::Render(int index, int numBarsToDraw, double minValue, double maxValue)
{
    for (unsigned int i = 0; i < indicators.size(); ++ i)
        indicators[i]->Render(index, numBarsToDraw, minValue, maxValue);
}