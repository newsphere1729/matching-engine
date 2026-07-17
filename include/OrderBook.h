#pragma once
#include "Order.h"
#include <map>
#include <queue>
#include <unordered_map>
#include <iostream>

class OrderBook {
private:
    std::map<double, std::queue<Order>, std::greater<double>> buyBook;
    std::map<double, std::queue<Order>> sellBook;
    std::unordered_map<long, std::pair<double, bool>> orderIndex;

public:
    void addOrder(Order order);
    void matchBuyOrder(Order& order);
    void matchSellOrder(Order& order);
    void cancelOrder(long orderId);
    void printBook(int depth = 5);
};