#include "../include/OrderBook.h"
#include <iostream> // Ensure this is included for std::cout

void OrderBook::addOrder(Order order) {
    if (order.isBuy) {
        buyBook[order.price].push(order);
    } else {
        sellBook[order.price].push(order);
    }
}

void OrderBook::printBook(int depth) {
    std::cout << "----- ORDER BOOK -----\n";

    // 1. SELL SIDE
    std::cout << "SELL:\n";
    int count = 0;
    for (auto& entry : sellBook) {
        if (count >= depth)
            break;

        double price = entry.first;
        auto& q = entry.second;

        std::cout << "  " << price << " x " << q.size() << "\n";
        count++;
    } 

    // 2. BUY SIDE
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