#pragma once

#include "Order.h"
#include <map>
#include <queue>
#include <vector>
#include <iostream>

class OrderBook {
private:
    // Buy side: highest price first
    std::map<double, std::queue<Order>, std::greater<double>> buyBook;

    // Sell side: lowest price first
    std::map<double, std::queue<Order>> sellBook;

public:
    void addOrder(Order order);

    //NEW 
    void matchBuyOrder(Order& order);
    void matchSellOrder(Order& order);
    void printBook(int depth = 5);
};