#pragma once

struct Order {
    long orderId;
    bool isBuy;       // true = BUY, false = SELL
    double price;
    int quantity;
    long timestamp;   // used for time priority at same price level

    Order(long id, bool buy, double p, int qty, long ts)
        : orderId(id), isBuy(buy), price(p), quantity(qty), timestamp(ts) {}
};