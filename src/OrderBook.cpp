#include "../include/OrderBook.h"
#include <iostream>
#include <algorithm> // for std::min

void OrderBook::addOrder(Order order) {
    if (order.isBuy) {
        matchBuyOrder(order);

        if (order.quantity > 0) {
            buyBook[order.price].push(order);
        }
    } else {
        matchSellOrder(order);

        if (order.quantity > 0) {
            sellBook[order.price].push(order);
        }
    }
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
    for (auto& [price, q] : sellBook) {
        if (count++ >= depth) break;
        int totalQty = 0;
        std::queue<Order> temp = q; // copy so we don't destroy original
        while (!temp.empty()) { totalQty += temp.front().quantity; temp.pop(); }
        std::cout << "  " << price << " x " << totalQty << " (" << q.size() << " orders)\n";
    }
    std::cout << "BUY:\n";
    count = 0;
    for (auto& [price, q] : buyBook) {
        if (count++ >= depth) break;
        int totalQty = 0;
        std::queue<Order> temp = q;
        while (!temp.empty()) { totalQty += temp.front().quantity; temp.pop(); }
        std::cout << "  " << price << " x " << totalQty << " (" << q.size() << " orders)\n";
    }
    std::cout << "-----------------------\n";
}

    // BUY SIDE
    std::cout << "BUY:\n";
    count = 0;

    for (auto& entry : buyBook) {
        if (count >= depth)
            break;

        double price = entry.first;
        auto& q = entry.second;

        std::cout << "  " << price << " x " << q.size() << "\n";
        count++;
    }

    std::cout << "-----------------------\n";
}