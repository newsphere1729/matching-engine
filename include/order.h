#pragma once

struct Order {
    long orderId;
    bool isBuy;
    double price;
    int quantity;
    long timestamp;

    Order(long id, bool buy, double p, int qty, long ts)
        : orderId(id), isBuy(buy), price(p), quantity(qty), timestamp(ts) {}
};