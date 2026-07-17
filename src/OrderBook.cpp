#include "../include/OrderBook.h"
#include <iostream>
#include <algorithm> // for std::min

void OrderBook::addOrder(Order order) {
    if (order.isBuy) {
        matchBuyOrder(order);
        if (order.quantity > 0) {
            buyBook[order.price].push(order);
            orderIndex[order.orderId] = {order.price, true};
        }
    } else {
        matchSellOrder(order);
        if (order.quantity > 0) {
            sellBook[order.price].push(order);
            orderIndex[order.orderId] = {order.price, false};
        }
    }
}

void OrderBook::cancelOrder(long orderId) {
    auto it = orderIndex.find(orderId);
    if (it == orderIndex.end()) {
        std::cout << "Cancel failed: order " << orderId << " not found\n";
        return;
    }

    double price = it->second.first;
    bool isBuy = it->second.second;

    if (isBuy) {
        auto priceIt = buyBook.find(price);
        if (priceIt != buyBook.end()) {
            std::queue<Order>& q = priceIt->second;
            std::queue<Order> newQ;
            while (!q.empty()) {
                if (q.front().orderId != orderId) newQ.push(q.front());
                q.pop();
            }
            q = newQ;
            if (q.empty()) buyBook.erase(priceIt);
        }
    } else {
        auto priceIt = sellBook.find(price);
        if (priceIt != sellBook.end()) {
            std::queue<Order>& q = priceIt->second;
            std::queue<Order> newQ;
            while (!q.empty()) {
                if (q.front().orderId != orderId) newQ.push(q.front());
                q.pop();
            }
            q = newQ;
            if (q.empty()) sellBook.erase(priceIt);
        }
    }

    orderIndex.erase(it);
    std::cout << "Order " << orderId << " cancelled\n";
}

void OrderBook::matchBuyOrder(Order& order) {
    while (order.quantity > 0 && !sellBook.empty()) {

        auto bestSell = sellBook.begin();   // Lowest sell price

        if (bestSell->first > order.price)
            break;

        std::queue<Order>& q = bestSell->second;
        Order& resting = q.front();

        int tradedQty = std::min(order.quantity, resting.quantity);

        std::cout << "TRADE: "
                  << tradedQty
                  << " @ "
                  << bestSell->first
                  << " (buy#"
                  << order.orderId
                  << " x sell#"
                  << resting.orderId
                  << ")\n";

        order.quantity -= tradedQty;
        resting.quantity -= tradedQty;

        if (resting.quantity == 0) {
            q.pop();

            if (q.empty()) {
                sellBook.erase(bestSell);
            }
        }
    }
}

void OrderBook::matchSellOrder(Order& order) {
    while (order.quantity > 0 && !buyBook.empty()) {

        auto bestBuy = buyBook.begin();   // Highest buy price

        if (bestBuy->first < order.price)
            break;

        std::queue<Order>& q = bestBuy->second;
        Order& resting = q.front();

        int tradedQty = std::min(order.quantity, resting.quantity);

        std::cout << "TRADE: "
                  << tradedQty
                  << " @ "
                  << bestBuy->first
                  << " (sell#"
                  << order.orderId
                  << " x buy#"
                  << resting.orderId
                  << ")\n";

        order.quantity -= tradedQty;
        resting.quantity -= tradedQty;

        if (resting.quantity == 0) {
            q.pop();

            if (q.empty()) {
                buyBook.erase(bestBuy);
            }
        }
    }
}

void OrderBook::printBook(int depth) {
    std::cout << "----- ORDER BOOK -----\n";
    std::cout << "SELL:\n";
    int count = 0;
    for (auto& entry : sellBook) {
        if (count++ >= depth) break;
        double price = entry.first;
        std::queue<Order>& q = entry.second;
        int totalQty = 0;
        std::queue<Order> temp = q;
        while (!temp.empty()) { totalQty += temp.front().quantity; temp.pop(); }
        std::cout << "  " << price << " x " << totalQty << " (" << q.size() << " orders)\n";
    }
    std::cout << "BUY:\n";
    count = 0;
    for (auto& entry : buyBook) {
        if (count++ >= depth) break;
        double price = entry.first;
        std::queue<Order>& q = entry.second;
        int totalQty = 0;
        std::queue<Order> temp = q;
        while (!temp.empty()) { totalQty += temp.front().quantity; temp.pop(); }
        std::cout << "  " << price << " x " << totalQty << " (" << q.size() << " orders)\n";
    }
    std::cout << "-----------------------\n";
}